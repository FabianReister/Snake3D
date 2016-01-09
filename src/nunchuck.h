#ifndef NUNCHUCK_H
#define NUNCHUCK_H

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


enum NunchuckVariant{
    NUNCHUCK_WHITE,
    NUNCHUCK_BLACK
};

template <NunchuckVariant variant>
class Nunchuck
{
public:
    enum ButtonState : bool{
        PRESSED = 0,
        RELEASE = 1
    };


    Nunchuck();
    bool connect();
    bool init();
private:
    bool write(char* buf, unsigned int buf_length);
    bool read(char* buf, unsigned int buf_length);

    int _file;
    char* _filename = "/dev/i2c-2";
};

#endif // NUNCHUCK_H
