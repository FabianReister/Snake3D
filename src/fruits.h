#ifndef FRUITS_H
#define FRUITS_H

#include <deque>

#include "led.h"
#include "config.h"
#include "snake.h"

class Fruits
{
public:
    Fruits(const Snake* snake);
    void generateFruit();
private:
    const Snake* _snake;
    std::deque<Led> _fruits;

};

#endif // FRUITS_H
