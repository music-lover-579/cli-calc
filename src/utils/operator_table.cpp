#include "utils/operator_table.h"

const std::unordered_map<std::string, expr::OperatorInfo>& expr::get_node_factory_map() {
    // Static map
    static std::unordered_map<std::string, expr::OperatorInfo> node_factory_map = {
        {"pi", {0, false, INT_MAX, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 0) throw std::runtime_error("Syntax error: pi cannot take an argument");
            return std::make_unique<expr::PiNode>();
        }}},
        {"e", {0, false, INT_MAX, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 0) throw std::runtime_error("Syntax error: e cannot take an argument");
            return std::make_unique<expr::ENode>();
        }}},
        {"++", {1, false, 3, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 1) throw std::runtime_error("Syntax error: + expects 1 argument");
            return std::make_unique<expr::PositiveNode>(std::move(children[0]));
        }}},
        {"--", {1, false, 3, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 1) throw std::runtime_error("Syntax error: - expects 1 argument");
            return std::make_unique<expr::NegativeNode>(std::move(children[0]));
        }}},
        {"+", {2, false, 1, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 2) throw std::runtime_error("Syntax error: + expects 2 arguments");
            return std::make_unique<expr::AdditionNode>(std::move(children[0]), std::move(children[1]));
        }}},
        {"-", {2, false, 1, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 2) throw std::runtime_error("Syntax error: - expects 2 arguments");
            return std::make_unique<expr::SubtractionNode>(std::move(children[0]), std::move(children[1]));
        }}},
        {"*", {2, false, 2, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 2) throw std::runtime_error("Syntax error: * expects 2 arguments");
            return std::make_unique<expr::MultiplicationNode>(std::move(children[0]), std::move(children[1]));
        }}},
        {"/", {2, false, 2, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 2) throw std::runtime_error("Syntax error: / expects 2 arguments");
            return std::make_unique<expr::DivisionNode>(std::move(children[0]), std::move(children[1]));
        }}},
        {"sqrt", {1, false, 4, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 1) throw std::runtime_error("Syntax error: sqrt expects 1 argument");
            return std::make_unique<expr::PositiveNode>(std::move(children[0]));
        }}},
        {"!", {1, true, 3, false, [](std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
            if (children.size() != 1) throw std::runtime_error("Syntax error: ! expects 1 argument");
            return std::make_unique<expr::PositiveNode>(std::move(children[0]));
        }}},
    };

    return node_factory_map;
}

std::unique_ptr<expr::ExprNode> expr::create_node(const std::string& op, std::vector<std::unique_ptr<expr::ExprNode>>&& children) {
    const auto& node_factory_map = get_node_factory_map();
    
    // Check operator existence
    if (node_factory_map.find(op) == node_factory_map.end()) throw std::runtime_error("Syntax error: Operator '" + op + "' undefined");
    
    // Acquire specific lambda function
    auto node_info = node_factory_map.at(op);
    return node_info.node_func_(std::move(children));
}

bool expr::contains(const std::string& op) {
    const auto& node_factory_map = get_node_factory_map();
    return (node_factory_map.find(op) != node_factory_map.end());
}

expr::OperatorInfo expr::get_operator_info(const std::string& op) {
    const auto& node_factory_map = get_node_factory_map();
    
    // Check operator existence
    if (node_factory_map.find(op) == node_factory_map.end()) throw std::runtime_error("Syntax error: Operator '" + op + "' undefined");

    // Return the operator info
    return node_factory_map.at(op);
}
