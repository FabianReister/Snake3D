#include "nunchuck.h"

// base address
const static char NUNCHUCK_ADDRESS = 0x52;
// registers
const static char REG_JOYSTICK_X   = 0x00;
const static char REG_JOYSTICK_Y   = 0x01;
const static char REG_ACC_X        = 0x02;
const static char REG_ACC_Y        = 0x03;
const static char REG_ACC_Z        = 0x04;
const static char REG_MIXED        = 0x05;

template <NunchuckVariant variant>
Nunchuck<variant>::Nunchuck(I2C* i2c) : _i2c(i2c)
{
}


template <NunchuckVariant variant>
bool Nunchuck<variant>::isConnected()
{
    return _i2c->isConnected(&NUNCHUCK_ADDRESS);
}



template <>
bool Nunchuck<NUNCHUCK_WHITE>::init()
{
    if (!isConnected()){
        return false;
    }
    // 0x40, 0x00
    char buf1[] = {0x40, 0x00};

    if (!_i2c->Write(buf1, 2)){
        return false;
    }
    // 0x00
    char buf2[] = {0x00};
    if (!_i2c->Write(buf2, 1)){
        return false;
    }
    return true;

}

template <>
bool Nunchuck<NUNCHUCK_BLACK>::init()
{
    if (!isConnected()){
        return false;
    }
    // send 0xF0, 0x55
    char buf1[] = { char(0xF0), 0x55};
    if (!_i2c->Write(buf1, 2)){
        return false;
    }
    // send 0xFB, 0x00
    char buf2[] = { char(0xFB), 0x00};
    if (!_i2c->Write(buf2, 2)){
        return false;
    }
    return true;

}


template class Nunchuck<NUNCHUCK_BLACK>;
template class Nunchuck<NUNCHUCK_WHITE>;
