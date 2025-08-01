#pragma once

#include <cctype>
#include <vector>
#include <string>
#include <variant>
#include <utility>
#include <stdexcept>
#include "globals.h"
#include "data/datatype_decl.h"
#include "utils/expr_node.h"
#include "utils/operator_table.h"

namespace parser {

// Type of token
enum class TokenType {
    Numeral,
    Symbol,
    Operator,
    Bracket,
    Separator
};
// Content of token
typedef std::variant<types::Numeral, std::string> TokenContent;

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
 * @returns a std::pair, first item std::string::iterator pointing to the end of the token (next place, by STL convention), second item token type
 */
std::pair<std::string::iterator, TokenType> find_token_end(std::string::iterator token_begin, std::string::iterator expr_end);

/**
 * @brief Converts a string of a token to a Token.
 * 
 * @param token_begin iterator pointing to the begin of the token
 * @param token_end iterator pointing to the end of the token
 * @param token_type type of the token
 * @returns the Token converted from the std::string
 * @throw std::runtime_error if encounters an invalid number
 */
Token string_to_token(std::string::iterator token_begin, std::string::iterator token_end, TokenType token_type);

/**
 * @brief Recognizes the brackets and operators in the token array.
 * 
 * @param tokens the tokens of the expression
 */
void recognize(std::vector<Token>& tokens);

/**
 * @brief Checks whether a character is valid to be the start of a numeral.
 * 
 * @param ch the character to check
 * @note Including digits and the decimal point.
 */
inline bool is_numeral(char ch) { return std::isdigit(ch) || ch == '.'; }

/**
 * @brief Checks whether a character is valid to be the start of a symbol.
 * 
 * @param ch the character to check
 * @note Including all characters and the underline _.
 */
inline bool is_symbol_start(char ch) { return std::isupper(ch) || std::islower(ch) || ch == '_'; }

/**
 * @brief Checks whether a character is valid to be in the middle of a symbol.
 * 
 * @param ch the character to check
 * @note Including all characters, numbers, and the underline _.
 */
inline bool is_symbol_middle(char ch) { return is_symbol_start(ch) || std::isdigit(ch); }

/**
 * @brief Checks whether a string is a bracket.
 * 
 * @param str the string to check
 */
inline bool is_bracket(const std::string& str) { return str == "(" || str == ")" || str == "[" || str == "]" || str == "{" || str == "}"; }

}; // namespace parser
