#pragma once

#include "vector.h"

#include <cassert>

namespace snake3d
{

    class Led
    {
    public:
        Led(std::uint8_t x, std::uint8_t y, std::uint8_t z, bool state = false);

        bool operator==(const Led& rhs) const;

        template <typename T2>
        Led
        operator+(const Vector3D<T2>& rhs)
        {
            Led shifted = {addWithBoundingsCheck(this->_x, rhs.x),
                           addWithBoundingsCheck(this->_y, rhs.y),
                           addWithBoundingsCheck(this->_z, rhs.z)};
            return shifted;
        }

        template <typename T2>
        const Led&
        operator+=(const Vector3D<T2>& rhs)
        {
            *this = *this + rhs;
            return *this;
        }

        template <typename T2>
        Led
        operator-(const Vector3D<T2>& rhs)
        {
            Led shifted = {addWithBoundingsCheck(this->_x, -rhs.x),
                           addWithBoundingsCheck(this->_y, -rhs.y),
                           addWithBoundingsCheck(this->_z, -rhs.z)};
            return shifted;
        }

        template <typename T2>
        const Led&
        operator-=(const Vector3D<T2>& rhs)
        {
            *this = *this - rhs;
            return *this;
        }

        static std::uint8_t _cube_size;

        static Led randomCreate(std::uint8_t start = 0, std::uint8_t end = _cube_size - 1);

        [[nodiscard]] std::uint8_t x() const;
        void x(const std::uint8_t& value);

        [[nodiscard]] std::uint8_t y() const;
        void y(const std::uint8_t& value);

        [[nodiscard]] std::uint8_t z() const;
        void z(const std::uint8_t& value);

    private:
        // vector elements
        std::uint8_t _x, _y, _z;
        bool _state;

        template <typename T2>
        std::uint8_t
        addWithBoundingsCheck(std::uint8_t a, T2 b)
        {
            float sum = static_cast<float>(a) + float(b);

            if (sum > _cube_size - 1)
            {
                // sum is positive
                return sum - _cube_size;
            }
            if (sum < 0)
            {
                // sum is negative
                return _cube_size + sum + 1;
            }
            return sum;
        }
    };

} // namespace snake3d
