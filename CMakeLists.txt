cmake_minimum_required(VERSION 3.14)
project(feaplusplus)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(feaplusplus/include)

add_subdirectory(feaplusplus/src)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(runTests
    feaplusplus/tests/test_geometry.cpp
)

target_link_libraries(runTests gtest gtest_main common geometry material loads solvers fea)


add_test(NAME runTests COMMAND runTests)

include(GoogleTest)
gtest_discover_tests(runTests)
