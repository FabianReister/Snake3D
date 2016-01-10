cmake_minimum_required (VERSION 2.8)
project (Snake3D)

# for travis
set(CMAKE_CXX_COMPILER g++-4.8)
set(CMAKE_CC_COMPILER gcc-4.8)

# for threads
find_package (Threads)

# executable
add_executable(snake3d
 src/main.cpp
 src/i2c.cpp
 src/nunchuck.cpp
 src/ledcube.cpp
 src/snake.cpp
 src/fruits.cpp
 src/ticker.cpp
)
# if cmake version 3.1
#target_compile_features(snake3d PRIVATE cxx_range_for)
add_definitions(-std=c++11)

# linker - threads
target_link_libraries (snake3d ${CMAKE_THREAD_LIBS_INIT})
