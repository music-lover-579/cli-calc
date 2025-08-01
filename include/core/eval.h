#pragma once

#include <vector>
#include <memory>
#include <stack>
#include <queue>
#include <stdexcept>
#include "data/datatype_decl.h"
#include "utils/expr_node.h"
#include "utils/operator_table.h"
#include "utils/symbol_table.h"
#include "core/parser.h"

namespace eval {

/**
 * @brief Builds an expression tree from a std::vector of tokens.
 * 
 * @param tokens_begin the iterator for the beginning of the token vector
 * @param tokens_end the iterator for the end of the token vector
 * @returns a std::unique_ptr pointing to the root node of the expression tree generated
 * @throw std::runtime_error if has syntax errors or invalid numbers
 */
std::unique_ptr<expr::ExprNode> build_expr_tree(
    std::vector<parser::Token>::const_iterator tokens_begin, std::vector<parser::Token>::const_iterator tokens_end);

/**
 * @brief Checks whether the brackets are paired correctly in the expression
 * 
 * @param tokens_begin the iterator for the beginning of the token vector
 * @param tokens_end the iterator for the end of the token vector
 * @returns `true` if correctly paired, `false` otherwise.
 */
bool check_bracket_matching(std::vector<parser::Token>::const_iterator tokens_begin, std::vector<parser::Token>::const_iterator tokens_end);

/**
 * @brief Checks whether two brackets are paired.
 * 
 * @param opening_bracket a std::string of the opening bracket
 * @param closing_bracket a std::string of the closing bracket
 * @returns `true` if correctly paired, `false` otherwise.
 */
inline bool is_bracket_match(const std::string& opening_bracket, const std::string& closing_bracket) { 
    return (opening_bracket == "(" && closing_bracket == ")") 
        || (opening_bracket == "[" && closing_bracket == "]") 
        || (opening_bracket == "{" && closing_bracket == "}");
}

} // namespace eval
