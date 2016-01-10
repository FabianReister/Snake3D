#include "ticker.h"

Ticker::Ticker(float frequency) : _loop_duration(1000000000.0 / frequency) // loop_dur is in nano seconds
{
}

void Ticker::attach(void (*fcn_ptr)())
{
    _fcn_ptr = fcn_ptr;
}

void Ticker::run()
{
    assert(_fcn_ptr != nullptr && "You have to provide a callback function to run ticker!");

    _thread = new std::thread(&Ticker::loop, this);

}

void Ticker::loop()
{
    // while system ok
    while(1){
        auto start = std::chrono::high_resolution_clock::now();

        // run attached callback function
        _fcn_ptr();

        // now get amount of time to wait
        auto elapsed = std::chrono::high_resolution_clock::now()-start;
        std::chrono::duration<double, std::nano> sleep_duration = _loop_duration - elapsed;
        // check if sleep > 0
        assert(sleep_duration.count() > 0.0);

        std::this_thread::sleep_for(sleep_duration);
    }
}

