#include "snake3d/mcp27013.h"

namespace snake3d
{

    MCP27013::MCP27013(std::experimental::observer_ptr<I2C> i2c, std::uint8_t address_msk) :
        IoExpander(i2c, SLAVE_BASE_ADDRESS & (0x03 & address_msk), 2)
    {
    }

    bool
    MCP27013::init()
    {
        if (not _i2c->connect(SLAVE_ADDRESS))
        {
            return false;
        }
        // set pins as output
        _i2c->Write(std::array<std::uint8_t, 3>{IODIRA, 0xFF, 0xFF});
        return true;
    }

    bool
    MCP27013::setOutputs(std::uint8_t data, std::uint8_t channel)
    {
        if (not _i2c->connect(SLAVE_ADDRESS))
        {
            return false;
        }
        _i2c->Write(std::array<std::uint8_t, 2>{static_cast<std::uint8_t>(GPIOA + channel), data});
        return true;
    }

    MCP27013::~MCP27013() = default;

} // namespace snake3d
