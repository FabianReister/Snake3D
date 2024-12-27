#include "snake3d/nunchuck.h"

namespace snake3d::nunchuck
{

    // base address
    const uint8_t Nunchuck::SLAVE_ADDRESS;

    Nunchuck::Nunchuck(std::experimental::observer_ptr<I2C> i2c) : _i2c(i2c)
    {
    }

    inline bool
    Nunchuck::Connect()
    {
        return _i2c->connect(SLAVE_ADDRESS);
    }

    bool
    Nunchuck::update()
    {
        Connect();
        uint8_t reg = 0x00;
        _i2c->Write(&reg, 1);
        return _i2c->Read(_raw_data.data(), 6);
    }

    const Data*
    Nunchuck::data()
    {
        _data.joystick.x = _raw_data[JOYSTICK_X];
        _data.joystick.y = _raw_data[JOYSTICK_Y];
        // TODO check if this really works. if not cast the first _raw_data[ACC...] to
        // uint16_t
        _data.accelerometer.x = static_cast<uint16_t>(_raw_data[ACCELEROMETER_X] << 2 |
                                                      (_raw_data[MIXED] & 0b00001100));
        _data.accelerometer.y = static_cast<uint16_t>(_raw_data[ACCELEROMETER_Y] << 2 |
                                                      (_raw_data[MIXED] & 0b00110000));
        _data.accelerometer.z = static_cast<uint16_t>(_raw_data[ACCELEROMETER_Z] << 2 |
                                                      (_raw_data[MIXED] & 0b11000000));
        _data.z_button = static_cast<ButtonState>(static_cast<bool>(_raw_data[MIXED] & 0b1));
        _data.c_button = static_cast<ButtonState>(static_cast<bool>(_raw_data[MIXED] & 0b10));
        return &_data;
    }

    Direction
    Nunchuck::getJoystickDirection(uint8_t joystick_value)
    {
        // 127 is 255/2 -> mid
        if (joystick_value < 127 - HYSTERESIS)
        {
            return Direction::NEGATIVE;
        }

        if (joystick_value > 127 + HYSTERESIS)
        {
            return Direction::POSITIVE;
        }

        return Direction::NONE;
    }

    bool
    Nunchuck::init(nunchuck::Variant variant)
    {
        if (!Connect())
        {
            return false;
        }

        switch (variant)
        {
            case nunchuck::WHITE:
            {
                // 0x40, 0x00
                const std::array<std::uint8_t, 2> buf1{0x40, 0x00};

                if (!_i2c->Write(buf1))
                {
                    return false;
                }
                // 0x00
                const std::array<std::uint8_t, 1> buf2{0x00};
                if (!_i2c->Write(buf2))
                {
                    return false;
                }
                break;
            }

            case nunchuck::BLACK:
            {
                // send 0xF0, 0x55
                const std::array<std::uint8_t, 2> buf1{0xF0, 0x55};

                if (!_i2c->Write(buf1))
                {
                    return false;
                }
                usleep(100000u);

                // send 0xFB, 0x00
                const std::array<std::uint8_t, 2> buf2{0xFB, 0x00};
                if (!_i2c->Write(buf2))
                {
                    return false;
                }
                break;
            }
            default:
                return false;
                break;
        }
        return true;
    }

} // namespace snake3d::nunchuck
