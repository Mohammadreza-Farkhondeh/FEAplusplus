cmake_minimum_required(VERSION 3.12)
project(libfea)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Add source files
file(GLOB_RECURSE FEA_SOURCES src/*.cpp)
add_library(fea ${FEA_SOURCES})

# Unit Tests
enable_testing()
add_executable(runTests tests/test_fea.cpp)
target_link_libraries(runTests fea)
add_test(NAME fea_tests COMMAND runTests)
