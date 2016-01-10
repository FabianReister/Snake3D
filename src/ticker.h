#ifndef TICKER_H
#define TICKER_H

#include <assert.h>
#include <thread>

#include <stdio.h>
#include <iostream>

class Ticker
{
public:
    Ticker(float frequency);
    void attach(void (*fcn_ptr)());
    void run();
private:
    std::chrono::duration<double, std::nano> _loop_duration;

    void (*_fcn_ptr)() = nullptr;

    std::thread* _thread;

    void loop();
};

#endif // TICKER_H
