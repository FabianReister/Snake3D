#https://github.com/kerberos-io/machinery/blob/master/cmake/External-Googletest.cmake
message("External project: Googletest")

include (ExternalProject)

# GIT

find_package(Git)

    if(NOT GIT_FOUND)
      message(ERROR "Cannot find git. git is required for Kerberos")
    endif()

    option(USE_GIT_PROTOCOL ON)
    if(NOT USE_GIT_PROTOCOL)
      set(git_protocol "http")
    else()
      set(git_protocol "git")
    endif()



# GTEST

ExternalProject_Add(googletest
  GIT_REPOSITORY https://github.com/google/googletest
  SOURCE_DIR googletest
  BUILD_IN_SOURCE 1
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  CMAKE_ARGS
    -DCMAKE_BUILD_TYPE:STRING=Release
    -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_BINARY_DIR}/thirdparty
    -Dgtest_force_shared_crt=ON
  INSTALL_DIR ${CMAKE_BINARY_DIR}/thirdparty
  INSTALL_COMMAND ""
)

set(GOOGLETEST_INCLUDE_DIR "${CMAKE_BINARY_DIR}/googletest/googletest/include/" "${CMAKE_BINARY_DIR}/googletest/googlemock/include/")
set(GOOGLETEST_LIBRARY_DIR ${CMAKE_BINARY_DIR}/googletest/)

include_directories(${GOOGLETEST_INCLUDE_DIR})
link_directories(${GOOGLETEST_LIBRARY_DIR})

set(GOOGLETEST_LIBRARIES "${GOOGLETEST_LIBRARY_DIR}googlemock/libgmock.a" "${GOOGLETEST_LIBRARY_DIR}googlemock/libgmock_main.a")

#
set(SNAKE3D_TEST_DEPENDENCIES ${SNAKE3D_TEST_DEPENDENCIES} googletest)
