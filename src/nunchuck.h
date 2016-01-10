#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#include "i2c.h"

#include <inttypes.h>

namespace nunchuck{

enum Variant{
    WHITE,
    BLACK
};

enum ButtonState : bool{
    PRESSED = 0,
    RELEASE = 1
};

struct Data{
    struct xy{
        unsigned char x,y;
    };

    struct xyz{
        unsigned char x,y,z;
    };

    xy joystick;
    xyz accelerometer;
    ButtonState c_button,z_button;
};

enum Direction: int8_t{
    NEGATIVE = -1,
    POSITIVE = 1,
    NONE = 0
};


template <Variant variant>
class Nunchuck
{
public:
    Nunchuck(I2C* i2c);
    bool isConnected();
    bool init();


    bool update();
    const Data* data();

    Direction getJoystickDirection(uint8_t joystick_value);


private:
    I2C* _i2c;
    char _raw_data[6] = {0};

    Data _data = {};

    enum RegAddress : uint8_t{
        // registers
        JOYSTICK_X   = 0x00,
        JOYSTICK_Y   = 0x01,
        ACCELEROMETER_X        = 0x02,
        ACCELEROMETER_Y        = 0x03,
        ACCELEROMETER_Z        = 0x04,
        MIXED        = 0x05
    };

    // base address
    const static char SLAVE_ADDRESS = 0x52;

    // hysteresis for joysticks
    const static uint8_t HYSTERESIS = 40;
};

}

#endif // NUNCHUCK_H
