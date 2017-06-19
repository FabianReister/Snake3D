#include "snake3d/led.h"

// add default value
uint8_t Led::_cube_size = 8;

uint8_t Led::x() const { return _x; }

void Led::x(const uint8_t &value) { _x = value; }
uint8_t Led::y() const { return _y; }

void Led::y(const uint8_t &value) { _y = value; }
uint8_t Led::z() const { return _z; }

void Led::z(const uint8_t &value) { _z = value; }
