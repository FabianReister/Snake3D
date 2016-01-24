
set(PThreadLib -pthread)

add_executable(allTests
 test.cpp
 ../src/snake.cpp
 ../src/fruits.cpp
  ../src/led.cpp
)


#add_dependencies(allTests ${SNAKE3D_TEST_DEPENDENCIES})


target_link_libraries(allTests
# ${GTEST_LIBRARIES}
# ${GMOCK_LIBRARIES}
gtest
gmock
 ${PThreadLib}
)

add_test(AllTests allTests)

#find_package(PkgConfig)
#pkg_check_modules(GTEST REQUIRED gtest>=1.7.0)
#pkg_check_modules(GMOCK REQUIRED gmock>=1.7.0)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${GMOCK_INCLUDE_DIRS}
)
