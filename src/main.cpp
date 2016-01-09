#include "nunchuck.h"
#include "i2c.h"
#include "snake.h"

I2C i2c;
Nunchuck<NUNCHUCK_BLACK> nunchuck(&i2c);

int main(int argc, char* argv[]){

    //i2c.init();
    //nunchuck.isConnected();

    Snake snake(10);

    return 0;
}
