#pragma once

#include <cassert>
#include <functional>
#include <thread>

namespace snake3d
{

    class Ticker
    {
    public:
        explicit Ticker(float frequency);

        using FnT = std::function<bool()>;

        void attach(FnT&& fn);
        void run();

        std::thread* thread();

    private:
        std::chrono::duration<double, std::nano> _loop_duration;

        FnT fn = nullptr;

        std::thread* _thread;

        void loop();
    };

} // namespace snake3d
