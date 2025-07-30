#include <iostream>
#include "globals.h"
#include "utils/expr_node.h"

int main(int argc, char* argv[]) {
    std::cout << "from test_data: Hello, world!\n";

    SymbolTable tab = {
        {"x", 1.14},
    };

    std::unique_ptr<expr::ExprNode> value1 = std::make_unique<expr::NumeralNode>(1.2);
    std::unique_ptr<expr::ExprNode> value2 = std::make_unique<expr::NumeralNode>(2.3);
    std::unique_ptr<expr::ExprNode> value3 = std::make_unique<expr::NumeralNode>(3.4);
    std::unique_ptr<expr::ExprNode> var1 = std::make_unique<expr::SymbolNode>("x");

    std::unique_ptr<expr::ExprNode> op1 = std::make_unique<expr::AdditionNode>(std::move(value1), std::move(value2));
    std::unique_ptr<expr::ExprNode> op2 = std::make_unique<expr::SubtractionNode>(std::move(value3), std::move(var1));
    std::unique_ptr<expr::ExprNode> op3 = std::make_unique<expr::MultiplicationNode>(std::move(op1), std::move(op2));

    try {
        std::cout << op3->evaluateAt(tab, {{"z", 1.14}}) << std::endl;
    }
    catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        return 1;
    }

    return 0;
}
