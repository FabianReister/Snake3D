cmake_minimum_required (VERSION 2.8)
project (Snake3D)

SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")
add_definitions(-std=c++11)



# executable
add_executable(snake3dsim
 sim_main.cpp
 ../src/snake.cpp
 ../src/fruits.cpp
)
