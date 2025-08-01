#include <iostream>
#include "core/parser.h"
#include "core/eval.h"
#include "globals.h"

int main(int argc, char* argv[]) {
    std::cout << "From test_functional: Hello, world!\n";
    
    try {
        std::string str;
        std::getline(std::cin, str, '\n');
        auto parse_result = parser::tokenize(str);
        auto expr_tree = eval::build_expr_tree(parse_result.begin(), parse_result.end());
        std::cout << expr_tree->evaluate({}) << std::endl;
    }
    catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }

    return 0;
}
