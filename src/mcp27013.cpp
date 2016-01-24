#include "mcp27013.h"

MCP27013::MCP27013(I2C* i2c, uint8_t address_msk) : IoExpander(i2c, SLAVE_BASE_ADDRESS & (0x03 & address_msk),2)
{}

bool MCP27013::init()
{
    if (!_i2c->connect(SLAVE_ADDRESS)){
        return false;
    }
    // set pins as output
    uint8_t buf[] = {IODIRA, 0xFF, 0xFF};
    _i2c->Write(buf, 3);
    return true;
}

bool MCP27013::setOutputs(uint8_t data, uint8_t channel)
{
    if (!_i2c->connect(SLAVE_ADDRESS)){
        return false;
    }
    uint8_t buf[] = { static_cast<uint8_t>(GPIOA+channel),data};
    _i2c->Write(buf,2);
    return true;
}

MCP27013::~MCP27013()
{

}
