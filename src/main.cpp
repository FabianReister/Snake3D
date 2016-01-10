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

//extern const Config CONFIG;


std::mutex mutex_i2c;
I2C i2c;

std::mutex mutex_game_status;
GameStatus game_status = STARTED;

nunchuck::Nunchuck<CONFIG.nunchuck_variant> _nunchuck(&i2c);

// snake
std::mutex mutex_snake;
Fruits fruits;
Snake snake(&fruits);
LedCube ledCube(&snake, &fruits);

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
        _nunchuck.update();
        mutex_i2c.unlock();

        // calculate snake movement direction from nunchuck data
        const nunchuck::Data* data = _nunchuck.data();
        nunchuck::Direction xJoystickDirection = _nunchuck.getJoystickDirection(data->joystick.x);
        nunchuck::Direction yJoystickDirection = _nunchuck.getJoystickDirection(data->joystick.y);

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

        // now update snake
        mutex_snake.lock();

        if( !snake.step(dir) ){
            mutex_game_status.lock();
            game_status = FINISHED;
            mutex_game_status.unlock();
        }
        mutex_snake.unlock();

    }else{
        return false;
    }

}

//------------------------------------------------------------------------------------
//!
//! \brief fast_loop is used for persistance of vision ,
//! TODO do we really need this?? or only call ledcube member fctn?
//!
bool fast_loop(){

    mutex_game_status.lock();
    GameStatus status = game_status;
    mutex_game_status.unlock();

    if (status == RUNNING){

        std::cout << "running fast loop " << std::endl;
        mutex_i2c.lock();
        char slave = 0x52;
        i2c.isConnected(&slave);
        mutex_i2c.unlock();

        return true;
    }else{
        return false;
    }
}


bool init(){
    // init game structure
    fruits.snake(&snake);

    // init bus devices
    i2c.init();
    //nunchuck.isConnected();


    // build up
    ledCube.updateLedStates();

}


int main(int argc, char* argv[]){

    if (init()){
        game_status = RUNNING;
    }else{
        return 1;
    }

    Ticker slow_ticker(CONFIG.slow_loop_frequency);
    slow_ticker.attach(slow_loop);
    slow_ticker.run();

    Ticker fast_ticker(CONFIG.fast_loop_frequency);
    fast_ticker.attach(fast_loop);
    fast_ticker.run();

    // slow and fast ticker will run as long game is running, wait for threads to stop
    slow_ticker.thread()->join();
    fast_ticker.thread()->join();

    printf("Snake length: %i \n", int(snake.length()));

    return 0;
}
