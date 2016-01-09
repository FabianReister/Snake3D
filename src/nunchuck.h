#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#include "i2c.h"

enum NunchuckVariant{
    NUNCHUCK_WHITE,
    NUNCHUCK_BLACK
};

template <NunchuckVariant variant>
class Nunchuck
{
public:
    enum ButtonState : bool{
        PRESSED = 0,
        RELEASE = 1
    };


    Nunchuck(I2C* i2c);
    bool isConnected();
    bool init();
private:
    I2C* _i2c;

};


#endif // NUNCHUCK_H
