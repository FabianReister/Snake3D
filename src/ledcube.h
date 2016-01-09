#ifndef LEDCUBE_H
#define LEDCUBE_H

#include <inttypes.h>

class LedCube
{
public:
    struct Led{
        uint8_t x,y,z;
    };


    LedCube();
};

#endif // LEDCUBE_H
