#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <inttypes.h>
#include "snake.h"
#include "fruits.h"
#include <assert.h>
#include "config.h"

#include <bitset>
#include "mcp27013.h"

class LedCube
{
public:
    LedCube(I2C* i2c, const Snake* snake, const Fruits* fruits);
    bool updateLedStates();
    void spinOnce();
private:
    I2C* _i2c;
    const Snake* _snake;
    const Fruits* _fruits;
    bool _led_state[CONFIG.cube_size][CONFIG.cube_size][CONFIG.cube_size];

    bool selectRow(uint8_t row);

    // TODO make it a param if using 1 or 2 channel ioexpanders
    IoExpander<CONFIG.io_expander_channel_count>* _ioexpander[CONFIG.cube_size/CONFIG.io_expander_channel_count];

};

#endif // LEDCUBE_H
