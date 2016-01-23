#include "nunchuck.h"
#include "i2c.h"
#include "snake.h"
#include "ledcube.h"
#include "ticker.h"
#include "config.h"
#include "game.h"
#include "fruits.h"

#include <stdio.h>
#include <iostream>

#include <mutex>
#include <thread>

//extern const Config CONFIG;


static std::mutex mutex_i2c;
static std::mutex mutex_game_status;
static std::mutex mutex_snake;
static std::mutex mutex_led_cube;

static GameStatus game_status = STARTED;


static I2C* i2c;
static nunchuck::Nunchuck<CONFIG.nunchuck_variant>* _nunchuck;
static Fruits* fruits;
static Snake* snake;
static LedCube* ledCube;



//------------------------------------------------------------------------------------

//!
//! \brief idle_loop updates what you can see (snake movement, ...)
//!
bool slow_loop(){

    mutex_game_status.lock();
    GameStatus status = game_status;
    mutex_game_status.unlock();

    if (status == RUNNING){
        std::cout << "running idle loop " << std::endl;

        // get new data from nunchuck (threadsafe)
        mutex_i2c.lock();
        _nunchuck->update();
        mutex_i2c.unlock();

        // calculate snake movement direction from nunchuck data
        const nunchuck::Data* data = _nunchuck->data();
        nunchuck::Direction xJoystickDirection = _nunchuck->getJoystickDirection(data->joystick.x);
        nunchuck::Direction yJoystickDirection = _nunchuck->getJoystickDirection(data->joystick.y);

        Direction dir = {0,0,0};
        if (data->c_button == nunchuck::PRESSED){ // z minux
            dir.z = -1;
        }else if(data->z_button == nunchuck::PRESSED){
            dir.z = 1;
        }else if(xJoystickDirection != nunchuck::NONE){
            dir.x = xJoystickDirection;
        }else if(yJoystickDirection != nunchuck::NONE){
            dir.y = yJoystickDirection;
        }

        printf("Direction x=%i, y=%i, z=%i \n", dir.x, dir.y, dir.z);

        // now update snake
        mutex_snake.lock();

        if( !snake->step(dir) ){
            mutex_game_status.lock();
            //         game_status = FINISHED;
            mutex_game_status.unlock();
        }

        mutex_led_cube.lock();

        // "redraw" led cube
        ledCube->updateLedStates();

        mutex_led_cube.unlock();
        mutex_snake.unlock();

        return true;
    }else{
        return false;
    }

}

//------------------------------------------------------------------------------------
//!
//! \brief fast_loop is used for persistance of vision ,
//!
void fast_loop(){

    while(1){
        mutex_game_status.lock();
        GameStatus status = game_status;
        mutex_game_status.unlock();

        if (status == RUNNING){

            std::cout << "running fast loop " << std::endl;
            mutex_i2c.lock();
            mutex_led_cube.lock();

            ledCube->spinOnce();

            mutex_led_cube.unlock();
            mutex_i2c.unlock();

        }else{
            return;
        }
    }
}


bool init(){

    i2c = new I2C();
    _nunchuck = new nunchuck::Nunchuck<CONFIG.nunchuck_variant>(i2c);
    fruits = new Fruits();
    snake = new Snake(fruits);
    ledCube = new LedCube(i2c,snake,fruits);



    // init game structure
    fruits->snake(snake);

    // init bus devices
    i2c->init();
    //nunchuck.isConnected();


    // build up
    ledCube->updateLedStates();

    _nunchuck->init();

    return true;
}


int main(){ //int argc, char* argv[]){

    if (init() || 1){
        game_status = RUNNING;
    }else{
        // TODO uncomment this
        printf("Could not init I2C bus");
        return 1;
    }

    Ticker slow_ticker(CONFIG.slow_loop_frequency);
    slow_ticker.attach(slow_loop);
    slow_ticker.run();

    //    std::thread fast_thread(fast_loop);

    // slow and fast ticker will run as long game is running, wait for threads to stop
    slow_ticker.thread()->join();
    //    fast_thread.join();

    printf("Snake length: %i \n", int(snake->length()));

    return 0;
}
