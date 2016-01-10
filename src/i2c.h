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

#include <thread>
#include <mutex>

class I2C
{
public:
    I2C();
    bool init();
    bool isConnected(const char* slave_adress);

    bool Write(char* buf, unsigned int buf_length);
    bool Read(char* buf, unsigned int buf_length);

private:
    int _file;
    const char* _filename = "/dev/i2c-2";    

};

#endif // I2C_H
