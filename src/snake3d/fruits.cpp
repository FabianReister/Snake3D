#include "snake3d/fruits.h"

#include <algorithm>

namespace snake3d
{

    Fruits::Fruits() = default;

    void
    Fruits::generateFruit()
    {
        assert(_snake != nullptr);

        bool fruit_set = false;
        Led fruit = {0, 0, 0};

        while (!fruit_set)
        {
            fruit = Led::randomCreate();
            fruit_set = true;
            for (const Led& snake_led : *(_snake->snake()))
            {
                if (snake_led == fruit || isFruit(fruit))
                {
                    fruit_set = false;
                    break;
                }
            }
        }
        _fruits.push_back(fruit);
    }

    bool
    Fruits::isFruit(const Led& led)
    {
        return std::ranges::any_of(_fruits,
                                   [&led](const Led& fruit) -> bool { return fruit == led; });
    }

    void
    Fruits::remove(const Led& fruit)
    {
        _fruits.erase(std::remove(_fruits.begin(), _fruits.end(), fruit), _fruits.end());
    }

    const std::vector<Led>*
    Fruits::fruits() const
    {
        return &_fruits;
    }

    void
    Fruits::snake(std::experimental::observer_ptr<const Snake> snake)
    {
        _snake = snake;
    }
} // namespace snake3d
