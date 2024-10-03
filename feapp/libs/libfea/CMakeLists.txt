cmake_minimum_required(VERSION 3.16)
project(libfea)


include_directories(include)

file(GLOB_RECURSE FEA_SOURCES src/*.cpp)
add_library(fea ${FEA_SOURCES})

enable_testing()
file(GLOB_RECURSE FEA_TESTS tests/*.cpp)
add_executable(runTests ${FEA_TESTS})
target_link_libraries(runTests fea)
add_test(NAME fea_tests COMMAND runTests)
