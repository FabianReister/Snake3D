cmake_minimum_required (VERSION 3.28)
project (Snake3D CXX)

# for clang-tidy and clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# Dependencies
################################################

# for threads
find_package (Threads REQUIRED)


#
# Libraries
################################################

add_library(snake3d_lib)

target_sources(snake3d_lib
    PUBLIC
    FILE_SET
        HEADERS
    TYPE
        HEADERS
    FILES
        source/snake3d/config.h
        source/snake3d/constants.h
        source/snake3d/game.h
        source/snake3d/i2c.h
        source/snake3d/nunchuck.h
        source/snake3d/led.h
        source/snake3d/ledcube.h
        source/snake3d/snake.h
        source/snake3d/fruits.h
        source/snake3d/ticker.h
        source/snake3d/mcp27013.h
        source/snake3d/configparser.h
        source/snake3d/ioexpander.h
)


target_sources(snake3d_lib
    PRIVATE
        source/snake3d/i2c.cpp
        source/snake3d/game.cpp
        source/snake3d/nunchuck.cpp
        source/snake3d/led.cpp
        source/snake3d/ledcube.cpp
        source/snake3d/snake.cpp
        source/snake3d/fruits.cpp
        source/snake3d/ticker.cpp
        source/snake3d/mcp27013.cpp
        source/snake3d/configparser.cpp
        source/snake3d/ioexpander.cpp
)

target_include_directories(snake3d_lib 
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/source>
)

target_compile_features(snake3d_lib 
    PUBLIC 
        cxx_std_20
)

target_link_libraries(snake3d_lib
    PUBLIC 
        Threads::Threads
)

add_library(snake3d::lib ALIAS snake3d_lib)


#
# Executables
################################################

# - the main executable

add_subdirectory(app/snake3d)

# - the simulator

option(SNAKE3D_BUILD_SIMULATOR "Build the simulated input device." ON)

if(${SNAKE3D_BUILD_SIMULATOR})
    add_subdirectory(app/sim)
endif()

#
# Installation
################################################

# - executables


install(
    TARGETS
        ${SNAKE3D_APPS}
    DESTINATION
        bin
)

# - libraries

install(
    TARGETS
        snake3d_lib
    DESTINATION
        lib
)


#
# Test
################################################

option(SNAKE3D_BUILD_TESTS "Build the tests." ON)

if(${SNAKE3D_BUILD_TESTS})
    add_subdirectory(test)
endif()
