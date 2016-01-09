#ifndef VECTOR_H
#define VECTOR_H

#include <inttypes.h>
#include "config.h"
#include <limits>



template <typename T1>
struct Vector{
    T1 x,y,z;
};


template struct Vector<int8_t>;
typedef Vector<int8_t> Direction;




#endif // VECTOR_H
