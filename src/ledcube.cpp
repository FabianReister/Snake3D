#include "ledcube.h"


LedCube::LedCube(I2C* i2c, const Snake *snake, const Fruits* fruits) : _i2c(i2c), _snake(snake), _fruits(fruits)
{
    for (uint8_t i = 0; i < CONFIG.cube_size/CONFIG.io_expander_channel_count; i++){
        // TODO use template IoExpander<MCP27013> and move to config
        _ioexpander[i] = new MCP27013(_i2c, i);
    }
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
    for(const Led& led : *(_fruits->fruits())){
        _led_state[led.x][led.y][led.z] = true;
    }

}

void LedCube::spinOnce()
{
    // if cube size is > 8 can't write
    assert(CONFIG.cube_size <= 8);

    for(uint16_t row = 0; row < CONFIG.cube_size; row++){
        //selectRow(row);
        for(uint16_t col = 0; col < CONFIG.cube_size; col++){
            std::bitset<CONFIG.cube_size> bits;
            for(uint16_t i = 0; i < CONFIG.cube_size; i++){
                bits[i] = _led_state[i][col][row];
                uint8_t data = bits.to_ulong();
                _ioexpander[i/CONFIG.io_expander_channel_count]->setOutputs(data,i%CONFIG.io_expander_channel_count);
            }


            // TODO adjust this
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(500));
        }
    }

}
