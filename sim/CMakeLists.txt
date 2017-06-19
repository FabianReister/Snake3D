cmake_minimum_required (VERSION 2.8)
project (Snake3D)

add_definitions(-std=c++11)

# executable
add_executable(snake3d_sim
 sim_main.cpp
)

target_link_libraries(snake3d_sim
  snake3d_lib
)
