#ifndef TICKER_H
#define TICKER_H

#include <assert.h>
#include <thread>

#include <iostream>
#include <stdio.h>

class Ticker {
public:
  explicit Ticker(float frequency);
  void attach(bool (*fcn_ptr)());
  void run();
  std::thread *thread() { return _thread; }

private:
  std::chrono::duration<double, std::nano> _loop_duration;

  bool (*_fcn_ptr)() = nullptr;

  std::thread *_thread;

  void loop();
};

#endif // TICKER_H
