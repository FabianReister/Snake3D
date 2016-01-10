#ifndef LED_H
#define LED_H

#include "config.h"
#include <inttypes.h>

#include "vector.h"

struct Led{
    // vector elements
    uint8_t x,y,z;
    Led(uint8_t _x, uint8_t _y, uint8_t _z, bool _state = false ){
        x = _x;
        y = _y;
        z = _z;

        state = _state;
    }

    bool state;

    bool operator==(const Led& rhs) const{
        return ( (this->x == rhs.x) && (this->y == rhs.y) && (this->z == rhs.z) );
    }

    template <typename T2>
    const Led operator+(const Vector3D<T2>& rhs) {
        Led shifted = { addWithBoundingsCheck(this->x, rhs.x),
                        addWithBoundingsCheck(this->y, rhs.y),
                        addWithBoundingsCheck(this->z, rhs.z)};
        return shifted;
    }

    template <typename T2>
    const Led& operator+=(const Vector3D<T2>& rhs){
        *this = *this + rhs;
        return *this;
    }

    template <typename T2>
    const Led operator-(const Vector3D<T2>& rhs){
        Led shifted = { addWithBoundingsCheck(this->x,-rhs.x),
                        addWithBoundingsCheck(this->y,-rhs.y),
                        addWithBoundingsCheck(this->z,-rhs.z)};
        return shifted;
    }

    template <typename T2>
    const Led& operator-=(const Vector3D<T2>& rhs){
        *this = *this - rhs;
        return *this;
    }

    template <typename T2>
    uint8_t addWithBoundingsCheck(uint8_t a, T2 b){
        float sum = float(a)+float(b);

        if ( sum > CONFIG.cube_size - 1){
            //sum is positive
            return sum - CONFIG.cube_size;
        }else if (sum < 0){
            //sum is negative
            return CONFIG.cube_size + sum + 1;
        }else{
            return sum;
        }
    }

};

#endif // LED_H
