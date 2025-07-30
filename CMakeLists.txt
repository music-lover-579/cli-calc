cmake_minimum_required(VERSION 3.10)
project(cli-calc)

# C++ standard 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -Wpedantic)

add_subdirectory(calc)
add_subdirectory(data)
add_subdirectory(numbers)
add_subdirectory(stats)
add_subdirectory(utils)

add_executable(cli-calc main.cpp)

target_link_libraries(cli-calc calc numbers stats utils data)

target_include_directories(cli-calc PUBLIC BEFORE ${CMAKE_SOURCE_DIR})

message(STATUS "Include dirs: ${CMAKE_INCLUDE_PATH}")
