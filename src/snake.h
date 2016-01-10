#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include <stdlib.h>

#include "vector.h"
#include "config.h"
#include "led.h"
#include "fruits.h"

class Fruits;

class Snake
{
public:
    Snake(Fruits* fruits, uint8_t start_size = 3);
    void direction(Direction dir);
    bool step();
    bool step(Direction dir);
    const std::deque<Led>* snake() const;

    size_t length();

private:
    Fruits* _fruits;
    // queues first element is snakes head
    std::deque<Led> _snake;
    Direction _dir;

};

#endif // SNAKE_H
