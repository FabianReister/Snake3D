#include "snake.h"

Snake::Snake(Fruits* fruits,uint8_t start_size) : _fruits(fruits)
{
    _dir = {0,0,0};
    // init snake with
    int dimension = rand() % 3 - 1;
    // direction should be either 1 or -1
    int direction = rand() % 2;
    if (direction == 0){
        direction = -1;
    }

    switch(dimension){
    case 0:
        _dir.x = direction;
        break;
    case 1:
        _dir.y = direction;
        break;
    case 2:
        _dir.z = direction;
        break;
    }

    // init snake somewhere but not in the outher 2 spheres
    Led led = Led::randomCreate(2,CONFIG.cube_size-2);
    _snake.push_front(led);

    for (uint8_t i = 1; i < start_size; i++){
        led += _dir;
        _snake.push_back(led);
    }

}

void Snake::direction(Direction dir)
{
    _dir = dir;
}

bool Snake::step()
{
    // remove snakes end
    _snake.pop_back();
    // create new head
    Led new_front = _snake.front() + _dir;

    // check if snake already has new_front as element -> got caught
    for (const Led& snake_element : _snake){
        if (snake_element == new_front){
            return false;
        }
    }

    _snake.push_front(new_front);
    return true;
}

bool Snake::step(Direction dir)
{
    direction(dir);
    return step();
}
const std::deque<Led>* Snake::snake() const
{
    return &_snake;
}

size_t Snake::length()
{
    return _snake.size();
}



