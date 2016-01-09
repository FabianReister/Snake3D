#ifndef SNAKE_H
#define SNAKE_H

#include <queue>
#include "ledcube.h"

class Snake
{
public:
    Snake();
private:
    std::queue<LedCube::Led> _snake;
};

#endif // SNAKE_H
