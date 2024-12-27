#pragma once

#include <snake3d/ioexpander.h>

#include <experimental/memory>

namespace snake3d
{

    class MCP27013 : public IoExpander
    {
    public:
        MCP27013(std::experimental::observer_ptr<I2C> i2c, uint8_t address_msk);
        bool init() override;
        bool setOutputs(uint8_t data, uint8_t channel) override;
        virtual ~MCP27013();

    private:
        enum Register : uint8_t
        {
            IODIRA = 0x00,
            IODIRB = 0x01,
            GPIOA = 0x12,
            GOIOB = 0x13
        };

        constexpr static uint8_t SLAVE_BASE_ADDRESS = 0x20;
    };

} // namespace snake3d
