file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_library(feaplusplus_src ${SOURCE_FILES})

target_link_libraries(feaplusplus_src PUBLIC feaplusplus_include)
