# Unit tests
add_executable(test_functional test_functional.cpp)
add_executable(test_data test_data.cpp)

# Link against the core modules
target_link_libraries(test_functional PRIVATE functional data utils)
target_link_libraries(test_data PRIVATE functional data utils)
