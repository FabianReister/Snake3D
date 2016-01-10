#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <inttypes.h>
#include "snake.h"
#include "fruits.h"
#include <assert.h>

#include <bitset>


class LedCube
{
public:
    LedCube(const Snake* snake, const Fruits* fruits);
    bool updateLedStates();
    void spinOnce();
private:
    const Snake* _snake;
    const Fruits* _fruits;
    bool _led_state[CONFIG.cube_size][CONFIG.cube_size][CONFIG.cube_size];

    bool selectRow(uint8_t row);

};

#endif // LEDCUBE_H
