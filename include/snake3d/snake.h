// Copyright 2017 Fabian Reister
#ifndef SNAKE_H
#define SNAKE_H

#include <stdlib.h>
#include <deque>

#include "config.h"
#include "fruits.h"
#include "led.h"
#include "vector.h"

class Fruits;

class Snake {
 public:
  Snake(Fruits *fruits, uint8_t start_size, uint8_t cube_size);
  void direction(Direction dir);
  bool step();
  bool step(Direction dir);
  const std::deque<Led> *snake() const;

  size_t length();

 private:
  Fruits *_fruits;
  uint8_t _cube_size;
  // queues first element is snakes head
  std::deque<Led> _snake;
  Direction _dir;
};

#endif  // SNAKE_H
