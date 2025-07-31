#include "core/parser.h"

std::vector<parser::Token> parser::tokenize(std::string expression) {
    std::vector<Token> tokens;

    // Removes the spaces in the expression
    remove_spaces(expression);

    // Iterate through the expression, build the token array
    auto token_begin = expression.begin();
    do {
        auto [token_end, token_type] = find_token_end(token_begin, expression.end()); // Find the token's end iterator
        tokens.push_back(string_to_token(token_begin, token_end, token_type)); // Parse this token and add to the tokens vector
        token_begin = token_end; // Move to the next token
    } while (token_begin != expression.end()); // Until reaches the end of the expressions

    // Recognize parenthesis and operators
    for (auto& [token_type, token_content] : tokens) {
        if (token_type == TokenType::Numeral) continue; // Is number, continue

        std::string token_string = std::get<std::string>(token_content);
        if (is_bracket(token_string)) token_type = TokenType::Bracket; // Is a bracket
        if (expr::contains(token_string)) token_type = TokenType::Operator; // Is an operator
    }
    
    return tokens;
}

void parser::remove_spaces(std::string& expression) {
    for (auto it = expression.begin(); it != expression.end(); ) {
        if (*it == ' ') it = expression.erase(it); // Is a space, then erase
        else ++it; // Otherwise move to next position
    }
}

std::pair<std::string::iterator, parser::TokenType> parser::find_token_end(std::string::iterator token_begin, std::string::iterator expr_end) {
    // Check if the range is valid
    if (token_begin == expr_end) throw std::out_of_range("Internal error: Attempt to parse after end of expression");
    
    if (is_numeral_start(*token_begin)) { // Is a numeral
        auto end_it = token_begin + 1;
        while (is_numeral_middle(*end_it) && end_it != expr_end) ++end_it; // Go on until the position is no longer a numeral
        return std::pair<std::string::iterator, TokenType>(end_it, TokenType::Numeral);
    }
    else if (is_symbol_start(*token_begin)) { // Is a symbol
        auto end_it = token_begin + 1;
        while (is_symbol_middle(*end_it) && end_it != expr_end) ++end_it; // Go on until the position is no longer a symbol
        return std::pair<std::string::iterator, TokenType>(end_it, TokenType::Symbol);
    }
    else { // Is an operator (Operators only have 1 character)
        return std::pair<std::string::iterator, TokenType>(token_begin + 1, TokenType::Symbol);
    }
}

parser::Token parser::string_to_token(std::string::iterator token_begin, std::string::iterator token_end, parser::TokenType token_type) {
    std::string token_string(token_begin, token_end); // Acquire the token string
    TokenContent token_content;

    switch (token_type) {
    case TokenType::Numeral:
        token_content = types::string_to_numeral(token_string);
        break;
    case TokenType::Symbol:
        token_content = token_string;
        break;
    }

    return Token(token_type, token_content);
}

