#ifndef CONFIG_H
#define CONFIG_H

#include <inttypes.h>
#include "nunchuck.h"


struct Config{
    // general
    uint8_t cube_size;
    // hardware
    nunchuck::Variant nunchuck_variant;
    // run settings
    float fast_loop_frequency;
    float idle_loop_frequency;
};

constexpr Config CONFIG{
    .cube_size = 8,
    .nunchuck_variant = nunchuck::BLACK,
    .fast_loop_frequency = 1000,
    .idle_loop_frequency = 1
};


#endif // CONFIG_H
