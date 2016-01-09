#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <inttypes.h>
#include "snake.h"


class LedCube
{
public:
    LedCube(const Snake* snake);
    bool updateLeds();
private:
    const Snake* _snake;


};

#endif // LEDCUBE_H
