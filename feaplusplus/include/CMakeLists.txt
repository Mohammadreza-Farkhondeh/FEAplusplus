file(GLOB HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
add_library(feaplusplus_include INTERFACE)
target_sources(feaplusplus_include INTERFACE ${HEADER_FILES})
target_include_directories(feaplusplus_include INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})