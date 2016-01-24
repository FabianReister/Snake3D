cmake_minimum_required (VERSION 2.8.3)
project (Snake3D)

add_subdirectory(src)

add_subdirectory(sim)


set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
#include(${CMAKE_SOURCE_DIR}/cmake/External-Googletest.cmake)

#add_subdirectory(test)
