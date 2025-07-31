#pragma once

#include <cctype>
#include <vector>
#include <string>
#include <variant>
#include <utility>
#include "globals.h"
#include "data/datatype_decl.h"

namespace parser {

// Type of token
enum class TokenType {
    Numeral,
    Symbol,
    Operator
};
// Content of token
typedef std::variant<types::Numeral, types::Symbol, std::string> TokenContent;

// Token
typedef std::pair<TokenType, TokenContent> Token;

/**
 * @brief Function to split the expression into tokens
 * 
 * @param expression the expression, a single std::string
 * @returns a std::vector containing the tokens
 */
std::vector<Token> tokenize(std::string expression);

/**
 * @brief Removes the spaces in a given expression.
 * 
 * @param expression a reference to a std::string containing the expression
 */
void remove_spaces(std::string& expression);

/**
 * @brief Finds the end of the token in the expression.
 * 
 * @param token_begin the iterator pointing to the begin of the token
 * @param expr_end the iterator pointing to the end of the expression
 * @returns a std::string::iterator pointing to the end of the token (next place, by STL convention)
 */
std::string::iterator find_token_end(std::string::const_iterator token_begin, std::string::const_iterator expr_end);

/**
 * @brief Converts a string of a token to a Token.
 * 
 * @param token_begin iterator pointing to the begin of the token
 * @param token_end iterator pointing to the end of the token
 * @returns the Token converted from the std::string
 * @throw std::runtime_error if encounters an invalid number
 */
Token string_to_token(std::string::const_iterator token_begin, std::string::const_iterator token_end);

}; // namespace parser
