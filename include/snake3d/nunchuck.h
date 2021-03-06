#ifndef NUNCHUCK_H
#define NUNCHUCK_H

#include <inttypes.h>
#include "i2c.h"
#include "vector.h"

namespace nunchuck {

enum Variant { WHITE, BLACK };

enum ButtonState : bool { PRESSED = 0, RELEASE = 1 };

struct Data {
  Vector2D<uint8_t> joystick;
  Vector3D<uint16_t> accelerometer;
  ButtonState c_button, z_button;
};

enum Direction : int8_t { NEGATIVE = -1, POSITIVE = 1, NONE = 0 };

class Nunchuck {
 public:
  explicit Nunchuck(I2C *i2c);
  bool Connect();

  bool init(nunchuck::Variant variant);

  bool update();
  const Data *data();

  static Direction getJoystickDirection(uint8_t joystick_value);

 private:
  I2C *_i2c;
  uint8_t _raw_data[6] = {0};

  Data _data = {};

  enum RegAddress : uint8_t {
    // registers
    JOYSTICK_X = 0,
    JOYSTICK_Y = 1,
    ACCELEROMETER_X = 2,
    ACCELEROMETER_Y = 3,
    ACCELEROMETER_Z = 4,
    MIXED = 5
  };

  // base address
  static const uint8_t SLAVE_ADDRESS = 0x52;

  // hysteresis for joysticks
  static const uint8_t HYSTERESIS = 40;
};

}  // namespace nunchuck

#endif  // NUNCHUCK_H
