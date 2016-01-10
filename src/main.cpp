#include "nunchuck.h"
#include "i2c.h"
#include "snake.h"
#include "ledcube.h"
#include "ticker.h"
#include "config.h"

#include <stdio.h>
#include <iostream>

//extern const Config CONFIG;


std::mutex mutex_i2c;
I2C i2c;


nunchuck::Nunchuck<CONFIG.nunchuck_variant> _nunchuck(&i2c);

std::mutex mutex_snake;
Snake snake(10);
LedCube ledCube(&snake);

//------------------------------------------------------------------------------------

//!
//! \brief idle_loop updates what you can see (snake movement, ...)
//!
void slow_loop(){
    std::cout << "running idle loop " << std::endl;

    // get new data from nunchuck (threadsafe)
    mutex_i2c.lock();
    _nunchuck.update();
    mutex_i2c.unlock();

    const nunchuck::Data* data = _nunchuck.data();


}

//------------------------------------------------------------------------------------
//!
//! \brief fast_loop is used for persistance of vision ,
//! TODO do we really need this?? or only call ledcube member fctn?
//!
void fast_loop(){
    std::cout << "running fast loop " << std::endl;
    mutex_i2c.lock();
    char slave = 0x52;
    i2c.isConnected(&slave);
    mutex_i2c.unlock();
}


bool init(){
    i2c.init();
    //nunchuck.isConnected();
    ledCube.updateLedStates();

}


int main(int argc, char* argv[]){

    init();

    Ticker slow_ticker(CONFIG.slow_loop_frequency);
    slow_ticker.attach(slow_loop);
    slow_ticker.run();

    Ticker fast_ticker(CONFIG.fast_loop_frequency);
    fast_ticker.attach(fast_loop);
    fast_ticker.run();

    while(1){}


    return 0;
}
