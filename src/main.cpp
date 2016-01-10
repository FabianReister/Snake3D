#include "nunchuck.h"
#include "i2c.h"
#include "snake.h"
#include "ledcube.h"
#include "ticker.h"
#include "config.h"

#include <stdio.h>
#include <iostream>

//extern const Config CONFIG;

I2C i2c;
nunchuck::Nunchuck<nunchuck::BLACK> _nunchuck(&i2c);


Snake snake(10);
LedCube ledCube(&snake);

//------------------------------------------------------------------------------------

//!
//! \brief idle_loop updates what you can see (snake movement, ...)
//!
void slow_loop(){
    std::cout << "running idle loop " << std::endl;

}

//------------------------------------------------------------------------------------
//!
//! \brief fast_loop is used for persistance of vision ,
//! TODO do we really need this?? or only call ledcube member fctn?
//!
void fast_loop(){

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
