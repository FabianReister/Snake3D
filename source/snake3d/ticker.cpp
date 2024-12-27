#include "snake3d/ticker.h"

namespace snake3d
{

    Ticker::Ticker(float frequency) :
        _loop_duration(1'000'000'000.0 / frequency) // loop_dur is in nano seconds
    {
    }

    void
    Ticker::attach(FnT&& fn)
    {
        this->fn = fn;
    }

    void
    Ticker::run()
    {
        assert(fn != nullptr && "You have to provide a callback function to run ticker!");

        _thread = new std::thread(&Ticker::loop, this);
    }

    void
    Ticker::loop()
    {
        // while system ok
        bool ok = true;
        while (ok)
        {
            auto start = std::chrono::high_resolution_clock::now();

            // run attached callback function
            ok = fn();

            // now get amount of time to wait
            const auto elapsed = std::chrono::high_resolution_clock::now() - start;
            std::chrono::duration<double, std::nano> sleep_duration = _loop_duration - elapsed;
            // check if sleep > 0
            assert(sleep_duration.count() > 0.0);

            std::this_thread::sleep_for(sleep_duration);
        }
    }

    std::thread*
    Ticker::thread()
    {
        return _thread;
    }
} // namespace snake3d
