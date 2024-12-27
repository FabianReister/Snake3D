#pragma once

#include <snake3d/nunchuck.h>

#include <array>

namespace snake3d::config
{

    struct Config
    {
        // general
        uint8_t cube_size;
        // hardware
        nunchuck::Variant nunchuck_variant;
        uint8_t io_expander_channel_count;
        // run settings;
        float slow_loop_frequency;
        // i2c
        std::array<char, 15> i2c_device;
    };

    /*
constexpr Config CONFIG = {
    // cube size
    8,
    // nunchuck variant
    nunchuck::BLACK,
    //io expander channel count
    2,
    // slow loop frequency
    1,
    // i2c device name
    "/dev/i2c-1"
};*/

} // namespace snake3d::config
