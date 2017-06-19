cmake_minimum_required (VERSION 2.8.7)
project (Snake3D)


add_definitions(-std=c++11)


# for threads
find_package (Threads REQUIRED)

include_directories(include)

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
)

# executable
add_executable(snake3d
    src/main.cpp
)
# if cmake version 3.1
#target_compile_features(snake3d PRIVATE cxx_range_for)
set(CMAKE_CXX_FLAGS "-std=c++11")

# linker - threads
target_link_libraries(snake3d_lib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(snake3d snake3d_lib)

install(TARGETS snake3d DESTINATION bin)

add_subdirectory(sim)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

# Download and unpack googletest at configure time
configure_file(test/External-Googletest.cmake
               googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gmock targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include"
                      "${gmock_SOURCE_DIR}/include")
endif()

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate


add_subdirectory(test)
