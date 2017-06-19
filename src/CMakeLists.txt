SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")

add_definitions(-DCMAKE_BUILD_TYPE=Debug)

# for threads
find_package (Threads REQUIRED)

include_directories(../include/)

add_library(snake3d_lib
    snake3d/i2c.cpp
    snake3d/nunchuck.cpp
    snake3d/led.cpp
    snake3d/ledcube.cpp
    snake3d/snake.cpp
    snake3d/fruits.cpp
    snake3d/ticker.cpp
    snake3d/mcp27013.cpp
    snake3d/configparser.cpp
)

# executable
add_executable(snake3d
    main.cpp
)
# if cmake version 3.1
#target_compile_features(snake3d PRIVATE cxx_range_for)
set(CMAKE_CXX_FLAGS "-std=c++11")

# linker - threads
target_link_libraries(snake3d_lib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(snake3d snake3d_lib)

install(TARGETS snake3d DESTINATION bin)
