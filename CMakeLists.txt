cmake_minimum_required (VERSION 2.8)
project (Snake3D)
add_executable(snake3d
 src/main.cpp
 src/i2c.cpp
 src/nunchuck.cpp
 src/ledcube.cpp
 src/snake.cpp
)
# if cmake version 3.1
#target_compile_features(snake3d PRIVATE cxx_range_for)
add_definitions(-std=c++11)

