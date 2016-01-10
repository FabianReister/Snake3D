#include "fruits.h"

Fruits::Fruits()
{
}

void Fruits::generateFruit()
{
    assert(_snake != nullptr);

    bool fruit_set = false;
    Led fruit = {0,0,0};

    while(!fruit_set){
        fruit = { uint8_t(rand() % (CONFIG.cube_size-1)),
                  uint8_t(rand() % (CONFIG.cube_size-1)),
                  uint8_t(rand() % (CONFIG.cube_size-1))
                };
        fruit_set = true;
        for (const Led& snake_led : *(_snake->snake())){
            if (snake_led == fruit){
                fruit_set = false;
                break;
            }
        }
    }
    _fruits.push_front(fruit);
}
