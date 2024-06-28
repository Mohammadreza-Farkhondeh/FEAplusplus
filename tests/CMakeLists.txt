add_executable(runTests
    test_geometry.cpp
    # test_fea.cpp
    # test_loads.cpp
    # test_material.cpp
    # test_solvers.cpp
)

target_link_libraries(runTests gtest gtest_main common)

add_test(NAME runTests COMMAND runTests)

include(GoogleTest)
gtest_discover_tests(runTests)
