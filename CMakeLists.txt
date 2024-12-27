cmake_minimum_required (VERSION 3.21)
project (Snake3D)

# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# Dependencies
################################################

# for threads
find_package (Threads REQUIRED)


#
# Libraries
################################################

add_library(snake3d_lib
    src/snake3d/i2c.cpp
    src/snake3d/nunchuck.cpp
    src/snake3d/led.cpp
    src/snake3d/ledcube.cpp
    src/snake3d/snake.cpp
    src/snake3d/fruits.cpp
    src/snake3d/ticker.cpp
    src/snake3d/mcp27013.cpp
    src/snake3d/configparser.cpp
    src/snake3d/ioexpander.cpp
)

target_include_directories(snake3d_lib PUBLIC include)
target_compile_features(snake3d_lib 
    PUBLIC 
        cxx_std_23
    #PRIVATE
    #    cxx_ranges
)
target_link_libraries(snake3d_lib PUBLIC Threads::Threads)


#
# Executables
################################################

# executable
add_executable(snake3d
    src/main.cpp
)

target_link_libraries(snake3d snake3d_lib)


#
# Installation
################################################

install(TARGETS snake3d DESTINATION bin)


#
# Simulation
################################################

add_subdirectory(sim)


#
# Test
################################################

add_subdirectory(test)
