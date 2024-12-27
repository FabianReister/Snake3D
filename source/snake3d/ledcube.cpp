#include "ledcube.h"

#include <snake3d/led.h>
#include <snake3d/mcp27013.h>
#include <snake3d/snake.h>

#include <bitset>
#include <cassert>
#include <memory>
#include <thread>

namespace snake3d
{

    LedCube::LedCube(std::experimental::observer_ptr<I2C> i2c,
                     std::experimental::observer_ptr<const Snake> snake,
                     std::experimental::observer_ptr<const Fruits> fruits,
                     uint8_t cube_size,
                     uint8_t io_expander_channel_count) :
        _i2c(i2c),
        _snake(snake),
        _fruits(fruits),
        _cube_size(cube_size),
        _io_expander_channel_count(io_expander_channel_count)
    {
        for (std::uint8_t i = 0; i < _cube_size / _io_expander_channel_count; i++)
        {
            // TODO use template IoExpander<MCP27013> and move to Config::CONFIG
            _ioexpander[i] = std::make_unique<MCP27013>(_i2c, i);
        }
    }

    bool
    LedCube::updateLedStates()
    {
        // set everything to zero
        for (uint8_t x = 0; x < _cube_size; x++)
        {
            for (uint8_t y = 0; y < _cube_size; y++)
            {
                for (uint8_t z = 0; z < _cube_size; z++)
                {
                    _led_state[x][y][z] = false;
                }
            }
        }

        // set all leds ON for snake
        for (const Led& led : *(_snake->snake()))
        {
            _led_state[led.x()][led.y()][led.z()] = true;
        }

        // set led ON for fruits
        for (const Led& led : _fruits->fruits())
        {
            _led_state[led.x()][led.y()][led.z()] = true;
        }

        return true;
    }

    void
    LedCube::spinOnce()
    {
        // if cube size is > 8 can't write
        assert(_cube_size <= 8);

        for (uint16_t row = 0; row < _cube_size; row++)
        {
            // selectRow(row);
            for (uint16_t col = 0; col < _cube_size; col++)
            {
                std::bitset<constants::MAX_CUBE_SIZE> bits;
                for (uint16_t i = 0; i < _cube_size; i++)
                {
                    bits[i] = _led_state[i][col][row];
                    auto data = static_cast<std::uint8_t>(bits.to_ulong());
                    _ioexpander[i / _io_expander_channel_count]->setOutputs(
                        data, i % _io_expander_channel_count);
                }

                // TODO adjust this
                std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(500));
            }
        }
    }

    LedCube::~LedCube() = default;
} // namespace snake3d
