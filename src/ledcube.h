#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <inttypes.h>
#include "snake.h"
#include "fruits.h"
#include <assert.h>
#include "config.h"

#include <bitset>
#include <thread>

#include "mcp27013.h"

class LedCube
{
public:
    LedCube(I2C* i2c, const Snake* snake, const Fruits* fruits, uint8_t cube_size = 8);
    bool updateLedStates();
    void spinOnce();
private:
    I2C* _i2c;
    const Snake* _snake;
    const Fruits* _fruits;

    static constexpr uint8_t MAX_CUBE_SIZE = 8;

    const uint8_t _cube_size;
    bool _led_state[MAX_CUBE_SIZE][MAX_CUBE_SIZE][MAX_CUBE_SIZE];

    bool selectRow(uint8_t row);

    // TODO make array size variable
    IoExpander<Config::CONFIG.io_expander_channel_count>* _ioexpander[MAX_CUBE_SIZE];

};

#endif // LEDCUBE_H
