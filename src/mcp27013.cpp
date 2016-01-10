#include "mcp27013.h"

MCP27013::MCP27013(I2C* i2c, uint8_t address_msk) : IoExpander(i2c, SLAVE_BASE_ADDRESS & (0x03 & address_msk))
{}

bool MCP27013::init()
{
    _i2c->Connect(&SLAVE_ADDRESS);
    // set pins as output
    char buf[] = {IODIRA, char(0xFF), char(0xFF)};
    _i2c->Write(buf, 3);
}

bool MCP27013::setOutputs(uint8_t data, uint8_t channel)
{
    _i2c->Connect(&SLAVE_ADDRESS);
    char buf[] = {char(GPIOA+channel),char(data)};
    _i2c->Write(buf,2);
}
