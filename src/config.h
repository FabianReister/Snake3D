#ifndef CONFIG_H
#define CONFIG_H

#include <inttypes.h>


struct Config{
    uint8_t cube_size;
    float fast_loop_frequency;
    float idle_loop_frequency;
};

constexpr Config CONFIG{
    .cube_size = 8,
    .fast_loop_frequency = 1000,
    .idle_loop_frequency = 1
};


#endif // CONFIG_H
