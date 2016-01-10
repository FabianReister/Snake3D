#include "i2c.h"

I2C::I2C()
{
}

bool I2C::init()
{
    if ((_file = open(_filename, O_RDWR)) < 0) {
        printf("Failed to open the i2c bus.\n");
        return false;
    }

    return true;
}

bool I2C::isConnected(const char *slave_adress)
{
    if (ioctl(_file, I2C_SLAVE, slave_adress) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
    }
}

bool I2C::Write(char *buf, unsigned int buf_length)
{
    if ( write(_file,buf,buf_length) != 1) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to write to the i2c bus.\n");
    }
}

bool I2C::Read(char *buf, unsigned int buf_length)
{
    //char buf[10] = {0};
    // Using I2C Read
    if ( read(_file,buf,buf_length) != buf_length) {
        /* ERROR HANDLING: i2c transaction failed */
        printf("Failed to read from the i2c bus.\n");
    }

}
