#include "nunchuck.h"
#include "i2c.h"

I2C i2c;
Nunchuck<NUNCHUCK_BLACK> nunchuck(&i2c);

int main(int argc, char* argv[]){

    nunchuck.isConnected();

    return 0;
}
