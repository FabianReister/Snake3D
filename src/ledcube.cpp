#include "ledcube.h"


LedCube::LedCube(const Snake *snake, const Fruits* fruits) : _snake(snake), _fruits(fruits)
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

void LedCube::spinOnce()
{
    // if cube size is > 8 can't write
    assert(CONFIG.cube_size <= 8);

    for(uint16_t row = 0; row < CONFIG.cube_size; row++){
        //selectRow(row);
        for(uint16_t col = 0; col < CONFIG.cube_size; row++){
            std::bitset<CONFIG.cube_size> bits;
            for(uint16_t i = 0; i < CONFIG.cube_size; i++){
                bits[i] = _led_state[i][col][row];
            }
            uint8_t data = bits.to_ulong();

        }

    }
}
