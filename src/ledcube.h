#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <inttypes.h>
#include "snake.h"
#include "fruits.h"


class LedCube
{
public:
    LedCube(const Snake* snake, const Fruits* fruits);
    bool updateLedStates();
    void spin();
private:
    const Snake* _snake;
    const Fruits* _fruits;
    bool _led_state[CONFIG.cube_size][CONFIG.cube_size][CONFIG.cube_size];

};

#endif // LEDCUBE_H
