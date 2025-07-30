add_library(calc INTERFACE)

add_executable(calc_test calc_test.cpp)

target_link_libraries(calc_test utils data)

target_include_directories(calc INTERFACE BEFORE ${CMAKE_SOURCE_DIR})