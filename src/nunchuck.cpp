#include "nunchuck.h"

namespace nunchuck {

// base address
template <Variant variant>
const char Nunchuck<variant>::SLAVE_ADDRESS;


template <Variant variant>
Nunchuck<variant>::Nunchuck(I2C* i2c) : _i2c(i2c)
{
}


template <Variant variant>
bool Nunchuck<variant>::isConnected()
{
    return _i2c->isConnected(&SLAVE_ADDRESS);
}



template <>
bool Nunchuck<WHITE>::init()
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
bool Nunchuck<BLACK>::init()
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


template class Nunchuck<BLACK>;
template class Nunchuck<WHITE>;

}
