#include "ioexpander.h"

namespace snake3d
{

    IoExpander::IoExpander(std::experimental::observer_ptr<I2C> i2c,
                           unsigned char slave_address,
                           std::uint8_t channel_count) :
        _i2c(i2c), SLAVE_ADDRESS(slave_address), _channel_count(channel_count)
    {
    }

    bool
    IoExpander::setOutputs(std::uint8_t /*data*/, std::uint8_t /*channel*/)
    {
        return false;
    }

    IoExpander::~IoExpander() = default;

    bool
    IoExpander::init()
    {
        return false;
    }
} // namespace snake3d
