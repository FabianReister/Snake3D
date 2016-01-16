cmake_minimum_required (VERSION 2.8)
project (Snake3D)

# for threads
find_package (Threads REQUIRED)

set(SRCS
 i2c.cpp
 nunchuck.cpp
 ledcube.cpp
 snake.cpp
 fruits.cpp
 ticker.cpp
 ioexpander.cpp
 mcp27013.cpp
)

# executable
add_executable(snake3d
 main.cpp
 ${SRCS}
)
# if cmake version 3.1
#target_compile_features(snake3d PRIVATE cxx_range_for)
add_definitions(-std=c++11)

# linker - threads
target_link_libraries (snake3d ${CMAKE_THREAD_LIBS_INIT})
