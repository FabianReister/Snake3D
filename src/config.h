#ifndef CONFIG_H
#define CONFIG_H

#include <inttypes.h>
#include "nunchuck.h"


struct Config{
    // general
    uint8_t cube_size;
    // hardware
    nunchuck::Variant nunchuck_variant;
    uint8_t io_expander_channel_count;
    // run settings;
    float slow_loop_frequency;
    // i2c
    char i2c_device[15];
};

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
};


#endif // CONFIG_H
