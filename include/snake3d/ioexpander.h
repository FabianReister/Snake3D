#pragma once

#include <snake3d/i2c.h>

#include <cstdint>
#include <experimental/memory>

namespace snake3d
{

    // N for output register count. assume 8bit registers
    class IoExpander
    {
    public:
        enum Channel : std::uint8_t
        {
            CHANNEL_1,
            CHANNEL_2
        };

        IoExpander(std::experimental::observer_ptr<I2C> i2c,
                   unsigned char slave_address,
                   std::uint8_t channel_count);
        // setup eg pins as outputs
        virtual bool init();
        virtual bool setOutputs(std::uint8_t data, std::uint8_t channel = 0);
        virtual ~IoExpander();

    protected:
        std::experimental::observer_ptr<I2C> _i2c;
        const unsigned char SLAVE_ADDRESS;
        const std::uint8_t _channel_count;
    };

} // namespace snake3d
