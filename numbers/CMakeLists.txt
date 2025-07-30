add_library(numbers INTERFACE)

target_include_directories(numbers INTERFACE BEFORE ${CMAKE_SOURCE_DIR})