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
    return _i2c->connect(SLAVE_ADDRESS);
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
    _data.joystick.x = _raw_data[JOYSTICK_X];
    _data.joystick.y = _raw_data[JOYSTICK_Y];
    // TODO check if this really works. if not cast the first _raw_data[ACC...] to uint16_t
    _data.accelerometer.x =static_cast<uint16_t>( _raw_data[ACCELEROMETER_X] << 2 | (_raw_data[MIXED] & 0b00001100));
    _data.accelerometer.y = static_cast<uint16_t>(_raw_data[ACCELEROMETER_Y] << 2 | (_raw_data[MIXED] & 0b00110000));
    _data.accelerometer.z = static_cast<uint16_t>(_raw_data[ACCELEROMETER_Z] << 2 | (_raw_data[MIXED] & 0b11000000));
    _data.z_button = static_cast<ButtonState>(bool(_raw_data[MIXED] & 0b1));
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
    uint8_t buf1[] = { 0xF0, 0x55};
    if (!_i2c->Write(buf1, 2)){
        return false;
    }
    usleep(100000u);
    // send 0xFB, 0x00
    uint8_t buf2[] = { 0xFB, 0x00};
    if (!_i2c->Write(buf2, 2)){
        return false;
    }
    return true;

}


template class Nunchuck<BLACK>;
template class Nunchuck<WHITE>;

}
