cmake_minimum_required (VERSION 2.8)
project (Snake3D)

# for threads
find_package (Threads REQUIRED)

set(SRCS
 src/i2c.cpp
 src/nunchuck.cpp
 src/ledcube.cpp
 src/snake.cpp
 src/fruits.cpp
 src/ticker.cpp
 src/ioexpander.cpp
 src/mcp27013.cpp
)

# executable
add_executable(snake3d
 src/main.cpp
 ${SRCS}
)
# if cmake version 3.1
#target_compile_features(snake3d PRIVATE cxx_range_for)
add_definitions(-std=c++11)

# linker - threads
target_link_libraries (snake3d ${CMAKE_THREAD_LIBS_INIT})

# testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(PThreadLib -pthread)

add_executable(allTests
 test/test.cpp
 ${SRCS}
)
target_link_libraries(allTests ${GTEST_BOTH_LIBRARIES} ${PThreadLib} )
add_test(AllTests allTests)
