#ifndef LED_H
#define LED_H

#include "config.h"
#include <inttypes.h>
#include <assert.h>

#include "vector.h"

class Led{
public:

    Led(uint8_t x, uint8_t y, uint8_t z, bool state = false ):
        _x(x), _y(y), _z(z), _state(state)
    {
    }

    bool operator==(const Led& rhs) const{
        return ( (this->_x == rhs._x) && (this->_y == rhs._y) && (this->_z == rhs._z) );
    }

    template <typename T2>
    const Led operator+(const Vector3D<T2>& rhs) {
        Led shifted = { addWithBoundingsCheck(this->_x, rhs.x),
                        addWithBoundingsCheck(this->_y, rhs.y),
                        addWithBoundingsCheck(this->_z, rhs.z)};
        return shifted;
    }

    template <typename T2>
    const Led& operator+=(const Vector3D<T2>& rhs){
        *this = *this + rhs;
        return *this;
    }

    template <typename T2>
    const Led operator-(const Vector3D<T2>& rhs){
        Led shifted = { addWithBoundingsCheck(this->_x,-rhs.x),
                        addWithBoundingsCheck(this->_y,-rhs.y),
                        addWithBoundingsCheck(this->_z,-rhs.z)};
        return shifted;
    }

    template <typename T2>
    const Led& operator-=(const Vector3D<T2>& rhs){
        *this = *this - rhs;
        return *this;
    }
    static uint8_t _cube_size;

    static Led randomCreate(uint8_t start = 0, uint8_t end = _cube_size-1){
        assert(end < _cube_size);
        assert(start < end);
        return { uint8_t(rand() % (end-start) + start),
                    uint8_t(rand() % (end-start) + start),
                    uint8_t(rand() % (end-start) + start)
        };
    }

    uint8_t x() const;
    void x(const uint8_t &value);

    uint8_t y() const;
    void y(const uint8_t &value);

    uint8_t z() const;
    void z(const uint8_t &value);

private:

    // vector elements
    uint8_t _x,_y,_z;
    bool _state;

    template <typename T2>
    uint8_t addWithBoundingsCheck(uint8_t a, T2 b){
        float sum = float(a)+float(b);

        if ( sum > _cube_size - 1){
            //sum is positive
            return sum - _cube_size;
        }else if (sum < 0){
            //sum is negative
            return _cube_size + sum + 1;
        }else{
            return sum;
        }
    }


};

#endif // LED_H
