#include "core/eval.h"

std::unique_ptr<expr::ExprNode> eval::build_expr_tree(
    std::vector<parser::Token>::const_iterator tokens_begin, std::vector<parser::Token>::const_iterator tokens_end) {

    // Check bracket pairing
    if (!check_bracket_matching(tokens_begin, tokens_end)) throw std::runtime_error("Syntax error: Unpaired brackets");

    // Convert to Reverse Polish Notation
    std::queue<parser::Token> reverse_polish; // Queue for the reverse polish style tokens
    std::stack<parser::Token> operators;      // Stack for operators

    for (auto it = tokens_begin; it != tokens_end; ++it) { // Iterate through the tokens
        switch (it->first) {
        case parser::TokenType::Numeral: case parser::TokenType::Symbol: // Number or symbol
            reverse_polish.push(*it);
            break;
        case parser::TokenType::Operator: { // Operator
            std::string operator_name = std::get<std::string>(it->second);
            
            // Disambiguitate between infix +- and prefix +-
            if (operator_name == "+" || operator_name == "-") {
                if ((it == tokens_begin) || ((it - 1)->first != parser::TokenType::Numeral && (it - 1)->first != parser::TokenType::Symbol)) {
                    operator_name += operator_name; // Change + to ++, - to -- to avoid ambiguity
                }
            }

            // Normal logic
            auto info = expr::get_operator_info(operator_name);
            if (info.arity_ == 0) reverse_polish.push(*it); // Treat it as a number or a symbol
            else if ((info.arity_ == 1 && !info.postfix_) || info.arity_ >= 3) 
                operators.push(parser::Token(parser::TokenType::Operator, operator_name)); // Prefix operator
            else if (info.arity_ == 1 && info.postfix_) { // Postfix Unary operator
                while (true) {
                    if (operators.empty()) break; // Operator queue empty, break directly
                     
                    auto top_info = expr::get_operator_info(std::get<std::string>(operators.top().second)); // Operator info at operator stack top
                    if (top_info.precedence_ > info.precedence_) {
                        reverse_polish.push(std::move(operators.top())); // Push the top of the operators stack into RPN queue
                        operators.pop(); // Pop the operator stack
                    }
                    else break; // Exit the loop
                }
                reverse_polish.push(*it); // Push this operator into the RPN queue
            }
            else { // Binary operator
                while (true) {
                    if (operators.empty()) break; // Empty, directly break

                    auto top_info = expr::get_operator_info(std::get<std::string>(operators.top().second));
                    if (((top_info.precedence_ > info.precedence_)                                      // Higher precedence
                        || (top_info.precedence_ == info.precedence_ && !top_info.right_assoc_))        // Equal precedence and left assoc
                        && operators.top().first != parser::TokenType::Bracket) {                       // Not a parenthesis, not empty
                        
                        reverse_polish.push(std::move(operators.top())); // Push the top of the operators stack into RPN queue
                        operators.pop(); // Pop the operator stack
                    }
                    else break; // Exit the loop
                }
                operators.push(*it); // Push this operator into the operators stack
            }
            break;
        }
        case parser::TokenType::Bracket: {
            std::string paren = std::get<std::string>(it->second);
            if (paren == "(" || paren == "[" || paren == "{") operators.push(*it); // Opening parenthesis
            else { // Closing parenthesis
                std::string opening_paren;
                if (paren == ")") opening_paren = "(";
                else if (paren == "]") opening_paren = "[";
                else opening_paren = "{";

                while (!operators.empty() && std::get<std::string>(operators.top().second) != opening_paren) { // Push every operator to the queue
                    reverse_polish.push(std::move(operators.top())); // Push the top of the operators stack into RPN queue
                    operators.pop(); // Pop the operator stack
                }
                if (operators.empty()) throw std::runtime_error("Syntax error: Unpaired brackets");
                operators.pop(); // Discard the opening parenthesis
            }
            break;
        }
        case parser::TokenType::Separator: { // Comma separator
            while (!operators.empty()) {
                std::string op_str = std::get<std::string>(operators.top().second);
                if (op_str == "(" || op_str == "[" || op_str == "{") break;

                reverse_polish.push(std::move(operators.top())); // Push the top of the operators stack into RPN queue
                operators.pop(); // Pop the operator stack
            }
            if (operators.empty()) throw std::runtime_error("Syntax error: Misplaced comma or unpaired brackets");
            break;
        }
        } // switch (it->first)
    }
    while (!operators.empty()) { // Push the remaining operators into the expression
        reverse_polish.push(std::move(operators.top())); // Push the top of the operators stack into RPN queue
        operators.pop(); // Pop the operator stack
    }

    // Build expression tree from Reverse Polish Notation
    std::stack<std::unique_ptr<expr::ExprNode>> node_stack; // Stack for the node
    std::vector<std::unique_ptr<expr::ExprNode>> children_nodes; // Temporary vector for storing children nodes

    while (!reverse_polish.empty()) {
        auto token = reverse_polish.front(); // Take out the frontmost token
        reverse_polish.pop();

        switch (token.first) { // Should be either numeral, symbol, or operator
        case parser::TokenType::Numeral:
            node_stack.push(std::make_unique<expr::NumeralNode>(std::get<types::Numeral>(token.second)));
            break;
        case parser::TokenType::Symbol:
            node_stack.push(std::make_unique<expr::SymbolNode>(std::get<types::Symbol>(token.second)));
            break;
        case parser::TokenType::Operator: {
            std::string op_name = std::get<std::string>(token.second);
            auto op_info = expr::get_operator_info(op_name);
            for (int i = 0; i < op_info.arity_; ++i) {
                if (node_stack.empty()) { // If node stack is empty, then there are some errors
                    throw std::runtime_error("Syntax error: Operator '" + op_name + "' expects " + std::to_string(op_info.arity_)
                    + " arguments, received " + std::to_string(i));
                }

                children_nodes.push_back(std::move(node_stack.top()));
                node_stack.pop();
            }
            node_stack.push(expr::create_node(op_name, std::move(children_nodes)));
            children_nodes.clear(); // Reset
        }
        } // switch (token.first)
    }

    if (node_stack.size() != 1) throw std::runtime_error("Syntax error: Missing or redundant arguments");
    return std::move(node_stack.top()); // The root node
}

bool eval::check_bracket_matching(std::vector<parser::Token>::const_iterator tokens_begin, std::vector<parser::Token>::const_iterator tokens_end) {
    std::stack<std::string> brackets;

    for (auto it = tokens_begin; it != tokens_end; ++it) {
        if (it->first != parser::TokenType::Bracket) continue; // Not a bracket
        
        std::string bracket = std::get<std::string>(it->second);
        if (bracket == "(" || bracket == "[" || bracket == "{") brackets.push(bracket); // An opening bracket
        else { // A closing bracket
            if (!is_bracket_match(bracket, brackets.top())) return false; // Not paired
            brackets.pop();
        }

        return brackets.empty(); // Empty means all correctly paired, not empty means not correctly paired
    }
}
