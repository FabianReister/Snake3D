
add_executable(snake3d
  main.cpp
)

target_link_libraries(snake3d
  snake3d::lib
)

list(APPEND SNAKE3D_APPS snake3d)
