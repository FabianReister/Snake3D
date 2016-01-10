#include "nunchuck.h"
#include "i2c.h"
#include "snake.h"
#include "ledcube.h"
#include "ticker.h"

#include <thread>
#include <stdio.h>
#include <iostream>

I2C i2c;
Nunchuck<NUNCHUCK_BLACK> nunchuck(&i2c);


Snake snake(10);
LedCube ledCube(&snake);


void idle_loop(){
    std::cout << "running idle loop " << std::endl;

}








int main(int argc, char* argv[]){

    //i2c.init();
    //nunchuck.isConnected();
    ledCube.updateLedStates();


    Ticker ticker(1);
    ticker.attach(idle_loop);
    ticker.run();

    while(1){}


    return 0;
}
