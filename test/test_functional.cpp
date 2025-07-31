#include <iostream>
#include "core/parser.h"
#include "globals.h"

int main(int argc, char* argv[]) {
    std::cout << "From test_functional: Hello, world!\n";

    std::string str;
    std::getline(std::cin, str, '\n');
    auto parse_result = parser::tokenize(str);
    for (const auto& [token_type, token_content] : parse_result) {
        switch (token_type) {
        case parser::TokenType::Numeral:
            std::cout << "Numeral: " << std::get<types::Numeral>(token_content) << std::endl;
            break;
        case parser::TokenType::Symbol:
            std::cout << "Symbol: " << std::get<types::Symbol>(token_content) << std::endl;
            break;
        case parser::TokenType::Bracket:
            std::cout << "Bracket: " << std::get<std::string>(token_content) << std::endl;
            break;
        case parser::TokenType::Operator:
            std::cout << "Operator: " << std::get<std::string>(token_content) << std::endl;
            break;
        }
    }

    return 0;
}
