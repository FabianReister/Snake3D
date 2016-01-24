#include "ledcube.h"


LedCube::LedCube(I2C* i2c, const Snake *snake, const Fruits* fruits, uint8_t cube_size) :
    _i2c(i2c), _snake(snake), _fruits(fruits), _cube_size(cube_size)
{

    for (uint8_t i = 0; i <_cube_size/Config::CONFIG.io_expander_channel_count; i++){
        // TODO use template IoExpander<MCP27013> and move to Config::CONFIG
        _ioexpander[i] = new MCP27013(_i2c, i);
    }
}

bool LedCube::updateLedStates()
{
    // set everything to zero
    for (uint8_t x = 0; x < Config::CONFIG.cube_size; x++){
        for (uint8_t y = 0; y < Config::CONFIG.cube_size; y++){
            for (uint8_t z = 0; z < Config::CONFIG.cube_size; z++){
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

    return true;

}

void LedCube::spinOnce()
{
    // if cube size is > 8 can't write
    assert(_cube_size <= 8);

    for(uint16_t row = 0; row < _cube_size; row++){
        //selectRow(row);
        for(uint16_t col = 0; col < _cube_size; col++){
            std::bitset<MAX_CUBE_SIZE> bits;
            for(uint16_t i = 0; i < _cube_size; i++){
                bits[i] = _led_state[i][col][row];
                uint8_t data = static_cast<uint8_t>(bits.to_ulong());
                _ioexpander[i/Config::CONFIG.io_expander_channel_count]->setOutputs(data,i%Config::CONFIG.io_expander_channel_count);
            }


            // TODO adjust this
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(500));
        }
    }

}
