#ifndef I2C_H
#define I2C_H

#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

class I2C {
 public:
  I2C(const char *device);
  bool init();
  bool connect(uint8_t slave_adress);

  bool Write(uint8_t *buf, uint8_t buf_length);
  bool Read(uint8_t *buf, uint8_t buf_length);

 private:
  int _file;
  const char *_device;
};

#endif  // I2C_H
