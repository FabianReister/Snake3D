#ifndef FRUITS_H
#define FRUITS_H

#include <vector>
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
    bool isFruit(const Led* led);
    void remove(const Led* fruit);
    //setter
    void snake(const Snake* snake){_snake = snake;}
    //getter
    const std::vector<Led>* fruits() const {return &_fruits;}
private:
    const Snake* _snake;
    std::vector<Led> _fruits;

};

#endif // FRUITS_H
