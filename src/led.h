#ifndef LED_H
#define LED_H

#include "config.h"

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

    template <typename T2>
    const Led operator+(Vector<T2> v){
        Led shifted = { addWithBoundingsCheck(this->x, v.x),
                        addWithBoundingsCheck(this->y, v.y),
                        addWithBoundingsCheck(this->z, v.z)};
        return shifted;
    }

    template <typename T2>
    const Led& operator+=(Vector<T2> v){
        *this = *this + v;
        return *this;
    }

    template <typename T2>
    const Led operator-(Vector<T2> v){
        Led shifted = { addWithBoundingsCheck(this->x,-v.x),
                        addWithBoundingsCheck(this->y,-v.y),
                        addWithBoundingsCheck(this->z,-v.z)};
        return shifted;
    }

    template <typename T2>
    const Led& operator-=(Vector<T2> v){
        *this = *this - v;
        return *this;
    }

    template <typename T2>
    uint8_t addWithBoundingsCheck(uint8_t a, T2 b){

        float sum = float(a)+float(b);

        if ( sum > CUBE_SIZE - 1){
            //sum is positive
            return sum - CUBE_SIZE;
        }else if (sum < 0){
            //sum is negative
            return CUBE_SIZE + sum + 1;
        }else{
            return sum;
        }


    }


};

#endif // LED_H
