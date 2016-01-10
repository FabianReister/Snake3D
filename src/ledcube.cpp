#include "ledcube.h"


LedCube::LedCube(const Snake *snake) : _snake(snake)
{

}

bool LedCube::updateLedStates()
{
    // set everything to zero
    for (uint8_t x = 0; x < CONFIG.cube_size; x++){
        for (uint8_t y = 0; y < CONFIG.cube_size; y++){
            for (uint8_t z = 0; z < CONFIG.cube_size; z++){
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
