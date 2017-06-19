#ifndef IOEXPANDER_H
#define IOEXPANDER_H

#include <inttypes.h>
#include "snake3d/i2c.h"

// N for output register count. assume 8bit registers
class IoExpander {
 public:
  enum Channel : uint8_t { CHANNEL_1, CHANNEL_2 };

  IoExpander(I2C *i2c, unsigned char slave_address, uint8_t channel_count)
      : _i2c(i2c),
        SLAVE_ADDRESS(slave_address),
        _channel_count(channel_count) {}
  // setup eg pins as outputs
  virtual bool init() { return false; }
  virtual bool setOutputs(uint8_t data, uint8_t channel = 0) { return false; }
  virtual ~IoExpander() {}

 protected:
  I2C *_i2c;
  const unsigned char SLAVE_ADDRESS;
  const uint8_t _channel_count;
};

#endif  // IOEXPANDER_H
