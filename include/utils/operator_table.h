#pragma once

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

/**
 * @brief Acquires the node factory map.
 * 
 * @return a const reference to the static node factory map.
 */
const std::unordered_map<std::string, NodeFactory>& get_node_factory_map();

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

} // namespace expr
