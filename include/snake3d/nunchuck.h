#pragma once

#include <snake3d/i2c.h>
#include <snake3d/vector.h>

#include <array>
#include <experimental/memory>

namespace snake3d::nunchuck
{

    enum Variant
    {
        WHITE,
        BLACK
    };

    enum class ButtonState : bool
    {
        PRESSED = false,
        RELEASE = true
    };

    struct Data
    {
        Vector2D<uint8_t> joystick;
        Vector3D<uint16_t> accelerometer;
        ButtonState c_button, z_button;
    };

    enum class Direction : int8_t
    {
        NEGATIVE = -1,
        POSITIVE = 1,
        NONE = 0
    };

    class Nunchuck
    {
    public:
        explicit Nunchuck(std::experimental::observer_ptr<I2C> i2c);
        bool Connect();

        bool init(nunchuck::Variant variant);

        bool update();
        const Data* data();

        static Direction getJoystickDirection(uint8_t joystick_value);

    private:
        I2C* _i2c;
        std::array<std::uint8_t, 6> _raw_data{0};

        Data _data = {};

        enum RegAddress : uint8_t
        {
            // registers
            JOYSTICK_X = 0,
            JOYSTICK_Y = 1,
            ACCELEROMETER_X = 2,
            ACCELEROMETER_Y = 3,
            ACCELEROMETER_Z = 4,
            MIXED = 5
        };

        // base address
        static const uint8_t SLAVE_ADDRESS = 0x52;

        // hysteresis for joysticks
        static const uint8_t HYSTERESIS = 40;
    };

} // namespace snake3d::nunchuck
