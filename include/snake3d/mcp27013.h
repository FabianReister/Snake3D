#ifndef MCP27013_H
#define MCP27013_H

#include "ioexpander.h"

class MCP27013 : public IoExpander {
 public:
  MCP27013(I2C *i2c, uint8_t address_msk);
  bool init();
  bool setOutputs(uint8_t data, uint8_t channel);
  virtual ~MCP27013();

 private:
  enum Register : uint8_t {
    IODIRA = 0x00,
    IODIRB = 0x01,
    GPIOA = 0x12,
    GOIOB = 0x13
  };
  constexpr static uint8_t SLAVE_BASE_ADDRESS = 0x20;
};

#endif  // MCP27013_H
