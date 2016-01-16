#ifndef IOEXPANDER_H
#define IOEXPANDER_H

#include <inttypes.h>
#include "i2c.h"

// N for output register count. assume 8bit registers
template <uint8_t N>
class IoExpander
{
public:
    IoExpander(I2C* i2c, char slave_address);
    //setup eg pins as outputs
    virtual bool init(){}
    virtual bool setOutputs(uint8_t data, uint8_t channel = 0){}
protected:
    I2C* _i2c;
    const unsigned char SLAVE_ADDRESS;
};

#endif // IOEXPANDER_H
