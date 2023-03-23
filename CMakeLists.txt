cmake_minimum_required(VERSION 3.26)

project(
  dsa
  VERSION 1.0
  DESCRIPTION "Data structures and algorithms"
  LANGUAGES CXX C)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


include_directories(include
  build/_deps/googletest-src/googletest/include)

add_subdirectory(lib)

add_executable(
  test_dsa
  tests/test_dsa.cpp
)

enable_testing()

target_link_libraries(
  test_dsa
  lib
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_dsa)