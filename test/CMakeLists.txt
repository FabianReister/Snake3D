
find_package(GTest REQUIRED)

add_executable(allTests
 test.cpp
)

target_link_libraries(allTests
  PUBLIC
    GTest::gtest
)

target_link_libraries(allTests
  PUBLIC
    snake3d_lib
)

add_test(AllTests allTests)

