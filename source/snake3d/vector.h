#pragma once

#include <cstdint>

namespace snake3d
{

    template <typename T1>
    struct Vector3D
    {
        T1 x, y, z;
    };

    template <typename T1>
    struct Vector2D
    {
        T1 x, y;
    };

    // template struct Vector3D<int8_t>;
    // typedef Vector3D<int8_t> Direction;

    using Direction = Vector3D<std::int8_t>;

} // namespace snake3d
