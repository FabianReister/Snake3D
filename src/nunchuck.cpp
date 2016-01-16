#include "nunchuck.h"

namespace nunchuck {

// base address
template <Variant variant>
const uint8_t Nunchuck<variant>::SLAVE_ADDRESS;


template <Variant variant>
Nunchuck<variant>::Nunchuck(I2C* i2c) : _i2c(i2c)
{
}


template <Variant variant>
inline bool Nunchuck<variant>::Connect()
{
    return _i2c->Connect(SLAVE_ADDRESS);
}


template <Variant variant>
bool Nunchuck<variant>::update()
{
    Connect();
    uint8_t reg = 0x00;
    _i2c->Write(&reg,1);
    return _i2c->Read(_raw_data,6);
}

template <Variant variant>
const Data *Nunchuck<variant>::data()
{
    printf("raw data: %X, %X, %X, %X, %X, %X", _raw_data[0], _raw_data[1], _raw_data[2], _raw_data[3], _raw_data[4], _raw_data[5]);
    _data.joystick.x = _raw_data[0];
    _data.joystick.y = _raw_data[1];
    _data.accelerometer.x = uint16_t(_raw_data[2]) << 2 | (_raw_data[5] & 0b00001100);
    _data.accelerometer.y = uint16_t(_raw_data[3]) << 2 | (_raw_data[5] & 0b00110000);
    _data.accelerometer.z = uint16_t(_raw_data[4]) << 2 | (_raw_data[5] & 0b11000000);
    _data.z_button = static_cast<ButtonState>(bool(_raw_data[5] & 0b1));
    _data.c_button = static_cast<ButtonState>(bool(_raw_data[MIXED] & 0b10));
    return &_data;
}


template <Variant variant>
Direction Nunchuck<variant>::getJoystickDirection(uint8_t joystick_value)
{
    // 127 is 255/2 -> mid
    if (joystick_value < 127 - HYSTERESIS){
        return NEGATIVE;
    }else if(joystick_value > 127 + HYSTERESIS){
        return POSITIVE;
    }else{
        return NONE;
    }
}



template <>
bool Nunchuck<WHITE>::init()
{
    if (!Connect()){
        return false;
    }
    // 0x40, 0x00
	unsigned    char buf1[] = {0x40, 0x00};

    if (!_i2c->Write(buf1, 2)){
        return false;
    }
    // 0x00
    unsigned char buf2[] = {0x00};
    if (!_i2c->Write(buf2, 1)){
        return false;
    }
    return true;

}

template <>
bool Nunchuck<BLACK>::init()
{
    if (!Connect()){
        return false;
    }
    // send 0xF0, 0x55
    unsigned char buf1[] = { char(0xF0), 0x55};
    if (!_i2c->Write(buf1, 2)){
        return false;
    }
    sleep(0.1);
    // send 0xFB, 0x00
    unsigned char buf2[] = { char(0xFB), 0x00};
    if (!_i2c->Write(buf2, 2)){
        return false;
    }
    return true;

}


template class Nunchuck<BLACK>;
template class Nunchuck<WHITE>;

}
