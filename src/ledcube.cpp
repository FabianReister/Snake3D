#include "ledcube.h"


LedCube::LedCube(const Snake *snake) : _snake(snake)
{

}

bool LedCube::updateLedStates()
{
    // set everything to zero
    for (uint8_t x = 0; x < CUBE_SIZE; x++){
        for (uint8_t y = 0; y < CUBE_SIZE; y++){
            for (uint8_t z = 0; z < CUBE_SIZE; z++){
                _led_state[x][y][z] = false;
            }
        }
    }

    // set all leds ON for snake
    for (const Led& led : *(_snake->snake()) )  {
        _led_state[led.x][led.y][led.z] = true;
    }

    // set led ON for fruits


}
