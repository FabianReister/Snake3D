#pragma once

namespace snake3d
{

    enum class GameStatus
    {
        INIT,
        STARTED, // started but not running
        RUNNING,
        FINISHED,
        ERROR
    };

} // namespace snake3d
