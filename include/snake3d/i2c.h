#pragma once

#include <linux/i2c-dev.h>

#include <sys/ioctl.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <array>
#include <cstdint>
#include <cstdlib>

namespace snake3d
{

    class I2C
    {
    public:
        I2C(const char* device);
        bool init();
        bool connect(std::uint8_t slave_adress);

        template <std::size_t N>
        bool
        Write(const std::array<unsigned char, N>& arr)
        {
            return Write(arr.data(), arr.size());
        }

        bool Write(const uint8_t* buf, std::uint8_t buf_length);
        bool Read(std::uint8_t* buf, std::uint8_t buf_length);

    private:
        int _file;
        const char* _device;
    };

} // namespace snake3d
