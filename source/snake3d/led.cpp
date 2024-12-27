#include "snake3d/led.h"

#include <cstdlib>

namespace snake3d
{

    // add default value
    uint8_t Led::_cube_size = 8;

    uint8_t
    Led::x() const
    {
        return _x;
    }

    void
    Led::x(const uint8_t& value)
    {
        _x = value;
    }

    uint8_t
    Led::y() const
    {
        return _y;
    }

    void
    Led::y(const uint8_t& value)
    {
        _y = value;
    }

    uint8_t
    Led::z() const
    {
        return _z;
    }

    void
    Led::z(const uint8_t& value)
    {
        _z = value;
    }

    Led
    Led::randomCreate(uint8_t start, uint8_t end)
    {
        assert(end < _cube_size);
        assert(start < end);
        return {static_cast<uint8_t>(rand() % (end - start) + start),
                static_cast<uint8_t>(rand() % (end - start) + start),
                static_cast<uint8_t>(rand() % (end - start) + start)};
    }

    Led::Led(std::uint8_t x, std::uint8_t y, std::uint8_t z, bool state) :
        _x(x), _y(y), _z(z), _state(state)
    {
    }

    bool
    Led::operator==(const Led& rhs) const
    {
        return ((this->_x == rhs._x) && (this->_y == rhs._y) && (this->_z == rhs._z));
    }
} // namespace snake3d
