#include "fruits.h"

#include <algorithm>

Fruits::Fruits()
{
}

void Fruits::generateFruit()
{
    assert(_snake != nullptr);

    bool fruit_set = false;
    Led fruit = {0,0,0};

    while(!fruit_set){
        fruit = Led::randomCreate();
        fruit_set = true;
        for (const Led& snake_led : *(_snake->snake())){
            if (snake_led == fruit || isFruit(&fruit)){
                fruit_set = false;
                break;
            }
        }
    }
    _fruits.push_back(fruit);
}

bool Fruits::isFruit(const Led *led)
{
    for(const Led& fruit : _fruits){
        if (fruit == *led){
            return true;
        }
    }
    return false;
}

void Fruits::remove(Led *fruit)
{
    _fruits.erase(std::remove(_fruits.begin(), _fruits.end(), *fruit), _fruits.end());
}

