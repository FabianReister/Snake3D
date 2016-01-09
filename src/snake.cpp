#include "snake.h"

Snake::Snake(uint8_t start_size)
{
    _dir = {0,0,0};
    // init snake with
    int dimension = rand() % 3 - 1;
    // direction should be either 1 or -1
    int direction = rand() % 2;
    //if (direction == 0){
        direction = 1;
    //}

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
    Led led = { uint8_t(rand() % (CUBE_SIZE-2) + 2),
                uint8_t(rand() % (CUBE_SIZE-2) + 2),
                uint8_t(rand() % (CUBE_SIZE-2) + 2)};
    _snake.push_front(led);

    for (uint8_t i = 1; i < start_size; i++){
        // TODO check boundings for led
        led += _dir;
        _snake.push_back(led);
    }

}

void Snake::setDirection(Direction dir)
{
    _dir = dir;
}

bool Snake::step()
{
    // remove snakes end
    _snake.pop_back();
    // create new head
    Led new_front = _snake.back() + _dir;
    _snake.push_front(new_front);
}

bool Snake::step(Direction dir)
{
    setDirection(dir);
    step();
}
const std::deque<Led>* Snake::snake() const
{
    return &_snake;
}



