#include "snake3d/i2c.h"

#include <cstdio>

namespace snake3d
{

    I2C::I2C(const char* device) : _device(device)
    {
    }

    bool
    I2C::init()
    {
        if ((_file = open(_device, O_RDWR)) < 0)
        {
            printf("Failed to open the i2c bus.\n");
            return false;
        }

        return true;
    }

    bool
    I2C::connect(uint8_t slave_address)
    {
        if (ioctl(_file, I2C_SLAVE, slave_address) < 0)
        {
            printf("Failed to acquire bus access and/or talk to slave.\n");
            return false;
        }
        return true;
    }

    bool
    I2C::Write(const uint8_t* const buf, uint8_t buf_length)
    {
        if (write(_file, buf, buf_length) != 1)
        {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to write to the i2c bus.\n");
            return false;
        }
        return true;
    }

    bool
    I2C::Read(uint8_t* buf, uint8_t buf_length)
    {
        // char buf[10] = {0};
        // Using I2C Read
        if (read(_file, buf, buf_length) != buf_length)
        {
            /* ERROR HANDLING: i2c transaction failed */
            printf("Failed to read from the i2c bus.\n");
            return false;
        }
        return true;
    }

} // namespace snake3d
