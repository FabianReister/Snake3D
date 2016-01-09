#include "nunchuck.h"
#include "i2c.h"
#include "snake.h"
#include "ledcube.h"

I2C i2c;
Nunchuck<NUNCHUCK_BLACK> nunchuck(&i2c);


Snake snake(10);

LedCube ledCube(&snake);

int main(int argc, char* argv[]){

    //i2c.init();
    //nunchuck.isConnected();


    return 0;
}
