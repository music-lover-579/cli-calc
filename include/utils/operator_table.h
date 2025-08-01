#pragma once

#include <climits>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>
#include <utility>
#include <stdexcept>
#include "data/datatype_decl.h"
#include "utils/expr_node.h"

namespace expr {

using NodeFactory = std::function<std::unique_ptr<expr::ExprNode>(std::vector<std::unique_ptr<expr::ExprNode>>&&)>;

struct OperatorInfo {
    int arity_;              // Arity of operator
    bool postfix_;           // Whether it is a postfix operator (such as !)
    int precedence_;         // Precedence of operator (higher means greater precedence)
    bool right_assoc_;       // Whether the operator is right-associative
    NodeFactory node_func_;  // The factory function for generating the node of the function
};

/**
 * @brief Acquires the node factory map.
 * 
 * @return a const reference to the static node factory map.
 */
const std::unordered_map<std::string, OperatorInfo>& get_node_factory_map();

/**
 * @brief Creates a node from the node factory map.
 * 
 * @param op a std::string of the operator
 * @param children the children nodes required by this operator
 * @returns The constructed node, a std::unique_ptr to a expr::exprNode.
 * @throws std::runtime_error if the argument numbers do not match the expected.
 * @throws std::runtime_error if the operator does not exist.
 */
std::unique_ptr<expr::ExprNode> create_node(const std::string& op, std::vector<std::unique_ptr<expr::ExprNode>>&& children);

/**
 * @brief Checks whether an operator is in the node factory map.
 * 
 * @param op a std::string of the operator
 * @returns `true` if the operator name does exist, `false` otherwise.
 */
bool contains(const std::string& op);

/**
 * @brief Acquires the operator info
 * 
 * @param op a std::string of the operator
 * @returns an expr::OperatorInfo struct containing the information
 * @throws std::runtime_error if the operator does not exist.
 */
OperatorInfo get_operator_info(const std::string& op);

} // namespace expr
