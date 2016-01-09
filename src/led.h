#ifndef LED_H
#define LED_H


struct Led{
    // vector elements
    uint8_t x,y,z;

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
        uint8_t min = std::numeric_limits<uint8_t>::min();
        uint8_t max = std::numeric_limits<uint8_t>::max();

        float sum = float(a)+float(b);

        if ( sum > max){
            //sum is positive
            return min + sum - max;
        }else if (sum < min){
            //sum is negative
            return max - min + sum + 1;
        }else{
            return sum;
        }


    }


};

#endif // LED_H
