#pragma once

#include <snake3d/led.h>

#include <experimental/memory>
#include <vector>

namespace snake3d
{

    // forward declaration
    class Snake;

    class Fruits
    {
    public:
        Fruits();
        void generateFruit();
        bool isFruit(const Led& led);
        void remove(Led fruit);

        // setter
        void snake(std::experimental::observer_ptr<const Snake> snake);
        // getter
        [[nodiscard]] const std::vector<Led>& fruits() const;

    private:
        std::experimental::observer_ptr<const Snake> _snake;
        std::vector<Led> _fruits;
    };

} // namespace snake3d
