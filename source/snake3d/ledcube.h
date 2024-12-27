#pragma once

#include <snake3d/constants.h>

#include <array>
#include <cstdint>
#include <experimental/memory>
#include <memory>

namespace snake3d
{

    class IoExpander;
    class I2C;
    class Fruits;
    class Snake;

    class LedCube
    {
    public:
        LedCube(std::experimental::observer_ptr<I2C> i2c,
                std::experimental::observer_ptr<const Snake> snake,
                std::experimental::observer_ptr<const Fruits> fruits,
                std::uint8_t cube_size,
                std::uint8_t io_expander_channel_count);
        bool updateLedStates();
        void spinOnce();

        ~LedCube();

    private:
        std::experimental::observer_ptr<I2C> _i2c;
        std::experimental::observer_ptr<const Snake> _snake;
        std::experimental::observer_ptr<const Fruits> _fruits;

        const std::uint8_t _cube_size;
        bool _led_state[constants::MAX_CUBE_SIZE][constants::MAX_CUBE_SIZE]
                       [constants::MAX_CUBE_SIZE];

        bool selectRow(std::uint8_t row);

        const std::uint8_t _io_expander_channel_count;

        std::array<std::unique_ptr<IoExpander>, constants::MAX_CUBE_SIZE> _ioexpander;
    };

} // namespace snake3d
