#include "nunchuck.h"

// base address
const static unsigned char NUNCHUCK_ADDRESS = 0x52;
// registers
const static unsigned char REG_JOYSTICK_X   = 0x00;
const static unsigned char REG_JOYSTICK_Y   = 0x01;
const static unsigned char REG_ACC_X        = 0x02;
const static unsigned char REG_ACC_Y        = 0x03;
const static unsigned char REG_ACC_Z        = 0x04;
const static unsigned char REG_MIXED        = 0x05;

template <NunchuckVariant variant>
Nunchuck<variant>::Nunchuck()
{
}


template <NunchuckVariant variant>
bool Nunchuck<variant>::connect()
{
    if ((_file = open(_filename, O_RDWR)) < 0) {
        printf("Failed to open the i2c bus.\n");
        return false;
    }

    if (ioctl(_file, I2C_SLAVE, NUNCHUCK_ADDRESS) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
    }

    return true;
}



template <>
bool Nunchuck<NUNCHUCK_WHITE>::init()
{
    if (!connect()){
        return false;
    }
    // 0x40, 0x00

    // 0x00

}

template <>
bool Nunchuck<NUNCHUCK_BLACK>::init()
{
    // send 0xF0, 0x55

    // send 0xFB, 0x00

}


template <NunchuckVariant variant>
bool Nunchuck<variant>::write(char *buf, unsigned int buf_length)
{
    if ( write(_file,buf,buf_length) != 1) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n");
    }
}


template <NunchuckVariant variant>
bool Nunchuck<variant>::read(char *buf, unsigned int buf_length)
{
    //char buf[10] = {0};
    // Using I2C Read
    if ( read(_file,buf,buf_length) != buf_length) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to read from the i2c bus.\n");
    }

}
