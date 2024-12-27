
add_executable(snake3d_sim
  main.cpp
)

target_link_libraries(snake3d_sim
  snake3d::lib
)

list(APPEND SNAKE3D_APPS snake3d_sim)
