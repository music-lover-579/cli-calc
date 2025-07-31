#include "core/parser.h"

std::vector<parser::Token> parser::tokenize(std::string expression) {
    std::vector<parser::Token> tokens;

    // Removes the spaces in the expression
    parser::remove_spaces(expression);

    // Iterate through the expression
    auto token_begin = expression.begin();
    do {
        auto token_end = parser::find_token_end(token_begin, expression.end()); // Find the token's end iterator
        tokens.push_back(parser::string_to_token(token_begin, token_end)); // Parse this token and add to the tokens vector
        token_begin = token_end; // Move to the next token
    } while (token_begin != expression.end()); // Until reaches the end of the expressions
    
    return tokens;
}

void parser::remove_spaces(std::string& expression) {
    for (auto it = expression.begin(); it != expression.end(); ) {
        if (*it == ' ') it = expression.erase(it); // Is a space, then erase
        else ++it; // Otherwise move to next position
    }
}

std::string::iterator parser::find_token_end(std::string::const_iterator token_begin, std::string::const_iterator expr_end) {

}

parser::Token parser::string_to_token(std::string::const_iterator token_begin, std::string::const_iterator token_end) {

}
