#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <inttypes.h>
#include "snake.h"


class LedCube
{
public:
    LedCube(const Snake* snake);
    bool updateLedStates();
    void spin();
private:
    const Snake* _snake;
    bool _led_state[CONFIG.cube_size][CONFIG.cube_size][CONFIG.cube_size];

};

#endif // LEDCUBE_H
