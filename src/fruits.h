#ifndef FRUITS_H
#define FRUITS_H

#include <deque>
#include <assert.h>

#include "led.h"
#include "config.h"
#include "snake.h"

// forward declaration
class Snake;

class Fruits
{
public:
    Fruits();
    void generateFruit();
    void snake(const Snake* snake){_snake = snake;}
private:
    const Snake* _snake;
    std::deque<Led> _fruits;

};

#endif // FRUITS_H
