#include "nunchuck.h"
#include "i2c.h"
#include "snake.h"
#include "ledcube.h"
#include "ticker.h"

#include <stdio.h>
#include <iostream>

extern const Config CONFIG;

I2C i2c;
nunchuck::Nunchuck<nunchuck::BLACK> _nunchuck(&i2c);


Snake snake(10);
LedCube ledCube(&snake);

//------------------------------------------------------------------------------------

//!
//! \brief idle_loop updates what you can see (snake movement, ...)
//!
void idle_loop(){
    std::cout << "running idle loop " << std::endl;

}

//------------------------------------------------------------------------------------
//!
//! \brief fast_loop is used for persistance of vision ,
//! TODO do we really need this?? or only call ledcube member fctn?
//!
void fast_loop(){

}




int main(int argc, char* argv[]){

    //i2c.init();
    //nunchuck.isConnected();
    ledCube.updateLedStates();


    Ticker ticker(CONFIG.idle_loop_frequency);
    ticker.attach(idle_loop);
    ticker.run();

    while(1){}


    return 0;
}
