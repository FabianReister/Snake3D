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
};

constexpr Config CONFIG{
    .cube_size = 8,
    .nunchuck_variant = nunchuck::BLACK,
    .io_expander_channel_count = 2,
    .slow_loop_frequency = 1
};


#endif // CONFIG_H
