#ifndef VECTOR_H
#define VECTOR_H

#include <inttypes.h>

template <typename T1>
struct Vector3D{
    T1 x,y,z;
};

template <typename T1>
struct Vector2D{
    T1 x,y;
};


//template struct Vector3D<int8_t>;
//typedef Vector3D<int8_t> Direction;

using Direction = Vector3D<int8_t>;


#endif // VECTOR_H
