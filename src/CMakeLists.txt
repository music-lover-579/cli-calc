# Source files for each module
add_library(core core/dispatcher.cpp core/parser.cpp functional/eval.cpp )
add_library(functional functional/numbers.cpp functional/stats.cpp)
add_library(utils utils/symbol_table.cpp utils/expr_node.cpp utils/operator_table.cpp)
add_library(data data/big_decimal.cpp)

# The main CLI executable
add_executable(cli-calc main.cpp)

# Link libraries to main program
target_link_libraries(cli-calc core functional utils data)
