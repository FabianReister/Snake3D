﻿#ifndef SNAKE_H
#define SNAKE_H

#include <queue>
#include <stdlib.h>

#include "vector.h"
#include "config.h"


class Snake
{
public:
    Snake(uint8_t start_size = 3);
    void setDirection(Direction dir);
    bool step();
    bool step(Direction dir);
private:
    // queue pop will give you last element in snake and push will add element to snakes head
    std::queue<Led> _snake;
    Direction _dir;

    Led shiftPoint(const Led* led);
};

#endif // SNAKE_H
