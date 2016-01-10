#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <inttypes.h>
#include "snake.h"


class LedCube
{
public:
    LedCube(const Snake* snake);
    bool updateLedStates();
private:
    const Snake* _snake;
    bool _led_state[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];

};

#endif // LEDCUBE_H
