#ifndef I2C_H
#define I2C_H

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <inttypes.h>

class I2C
{
public:
    I2C();
    bool init();
    bool Connect(uint8_t slave_adress);

    bool Write(uint8_t* buf, uint8_t buf_length);
    bool Read(uint8_t* buf, uint8_t buf_length);

private:
    int _file;
    const char* _filename = "/dev/i2c-1";    

};

#endif // I2C_H
