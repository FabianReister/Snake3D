#pragma once

#include <snake3d/fruits.h>
#include <snake3d/led.h>
#include <snake3d/vector.h>

#include <cstdlib>
#include <deque>
#include <experimental/memory>

namespace snake3d
{

    class Fruits;

    class Snake
    {
    public:
        Snake(std::experimental::observer_ptr<const Fruits> fruits,
              uint8_t start_size,
              uint8_t cube_size);
        void direction(Direction dir);
        bool step();
        bool step(Direction dir);
        const std::deque<Led>* snake() const;

        size_t length();

    private:
        std::experimental::observer_ptr<const Fruits> _fruits;
        uint8_t _cube_size;
        // queues first element is snakes head
        std::deque<Led> _snake;
        Direction _dir;
    };

} // namespace snake3d
