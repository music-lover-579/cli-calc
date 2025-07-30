#pragma once

#include <cmath>
#include <vector>
#include <memory>
#include <utility>
#include "data/datatype_decl.h"
#include "utils/symbol_table.h"

namespace expr {

/**
 * @class ExprNode
 * 
 * @brief Base class for the node of an expression tree.
 * @note This class is intended to be abstract, and should not be directly instantiated.
 */
class ExprNode {
protected:
    ExprNode() = default; // Default constructor

public:
    virtual ~ExprNode() = default;

    /**
     * @brief Evaluates the expression subtree with the provided symbol table.
     * 
     * @param symbols the symbol table
     * @return the evaluated result
     */
    virtual types::Numeral evaluate(const SymbolTable& symbols) const = 0; // Purely virtual

    /**
     * @brief Evaluates the expression subtree with the provided symbol table, with some symbols' values explicitly provided.
     * 
     * @param symbols the symbol table
     * @param variables the provided values of some symbols
     * @return the evaluated result
     */
    virtual types::Numeral evaluateAt(const SymbolTable& symbols, const std::unordered_map<types::Symbol, types::Numeral>& variables) const = 0;

    // Delete copy constructors, default move constructors
    ExprNode(const ExprNode& other) = delete;
    ExprNode& operator=(const ExprNode& other) = delete;
    ExprNode(ExprNode&& other) = default;
    ExprNode& operator=(ExprNode&& other) = default;
};

/**
 * @class NullaryNode
 * 
 * @brief Base class for nullary 'operators', such as constants pi, e, etc.
 * @note This class is intended to be abstract. It should never be directly instantiated.
 */
class NullaryNode : public ExprNode {
protected:
    /**
     * @brief Default constructor for NullaryNode.
     */
    NullaryNode() : ExprNode() {}

public:
    virtual ~NullaryNode() = default;
};

/**
 * @class UnaryNode
 * 
 * @brief Base class for unary operations, such as sqrt, factorial, etc.
 * @note This class is intended to be abstract. It should never be directly instantiated.
 */
class UnaryNode : public ExprNode {
protected:
    std::unique_ptr<ExprNode> child_; // Child node

    /**
     * @brief Default constructor for UnaryNode.
     */
    UnaryNode() : ExprNode(), child_(nullptr) {}

    /**
     * @brief Constructor for UnaryNode.
     * 
     * @param child rvalue reference of the children node of the 
     */
    UnaryNode(std::unique_ptr<ExprNode>&& child) : ExprNode(), child_(std::move(child)) {}

public:
    virtual ~UnaryNode() = default;
};

/**
 * @class BinaryNode
 * 
 * @brief Base class for binary operations, such as +, -, gcd, etc.
 * @note This class is intended to be abstract. It should never be directly instantiated.
 */
class BinaryNode : public ExprNode {
protected:
    std::unique_ptr<ExprNode> left_;  // Left child
    std::unique_ptr<ExprNode> right_; // Right child
    
    /**
     * @brief Default constructor for the binary node.
     */
    BinaryNode() : ExprNode(), left_(nullptr), right_(nullptr) {}

    /**
     * @brief Constructor of the binary node.
     * 
     * @param left rvalue reference to the pointer to left child
     * @param right rvalue reference to the pointer to right child
     */
    BinaryNode(std::unique_ptr<ExprNode>&& left, std::unique_ptr<ExprNode>&& right) : 
        ExprNode(), left_(std::move(left)), right_(std::move(right)) {}

public:
    virtual ~BinaryNode() = default;
};

/**
 * @class MultinaryNode
 * 
 * @brief Base class for multinary operations, such as avg, sum, etc.
 * @note This class is intended to be abstract. It should never be directly instantiated.
 */
class MultinaryNode : public ExprNode {
protected:
    std::vector<std::unique_ptr<ExprNode>> children_; // Children
    
    /**
     * @brief Default constructor of the multinary node.
     */
    MultinaryNode() : ExprNode(), children_() {}

    /**
     * @brief Constructor of the multinary node.
     * 
     * @param children rvalue reference to a std::vector holding std::unique_ptrs to the children nodes
     */
    MultinaryNode(std::vector<std::unique_ptr<ExprNode>>&& children) : ExprNode(), children_(std::move(children)) {}

public:
    virtual ~MultinaryNode() = default;
};

/**
 * @class NumeralNode
 * 
 * @brief Class for a single numeral.
 */
class NumeralNode : public ExprNode {
private:
    types::Numeral value_;

public:
    /**
     * @brief Default constructor.
     */
    NumeralNode() : ExprNode(), value_() {}

    /**
     * @brief Constructor for the Numeral.
     * 
     * @param value the value of the numeral
     */
    NumeralNode(const types::Numeral& value) : ExprNode(), value_(value) {};


    virtual ~NumeralNode() = default;

    virtual types::Numeral evaluate(const SymbolTable& symbols) const override final { return value_; }

    virtual types::Numeral evaluateAt(const SymbolTable& symbols, 
        const std::unordered_map<types::Symbol, types::Numeral>& variables) const override final {
        return value_;    
    }
};

/**
 * @class SymbolNode
 * 
 * @brief Class for a symbol.
 */
class SymbolNode : public ExprNode {
private:
    types::Symbol symbol_;

public:
    /**
     * @brief Default constructor.
     */
    SymbolNode() : ExprNode(), symbol_() {}

    /**
     * @brief Constructor for Symbol.
     * 
     * @param symbol name of the symbol
     */
    SymbolNode(const types::Symbol& symbol) : ExprNode(), symbol_(symbol) {}

    virtual ~SymbolNode() = default;

    virtual types::Numeral evaluate(const SymbolTable& symbols) const override final { return symbols.at(symbol_); }

    /**
     * @note This function prioritizes the variables first if there are name collisions.
     */
    virtual types::Numeral evaluateAt(const SymbolTable& symbols, 
        const std::unordered_map<types::Symbol, types::Numeral>& variables) const override final {
        auto it = variables.find(symbol_);
        if (it != variables.end()) return it->second; // Prioritizes variables
        return symbols.at(symbol_);
    }
};

/**
 * @class PiNode
 * 
 * @brief Class for the constant pi (3.1415926...)
 */
class PiNode : public NullaryNode {
private:
    static constexpr types::Numeral kValue = 3.1415926535897932385;

public:
    /**
     * @brief Default constructor.
     */
    PiNode() : NullaryNode() {}

    virtual types::Numeral evaluate(const SymbolTable& symbols) const override final { return kValue; }

    virtual types::Numeral evaluateAt(const SymbolTable& symbols, 
        const std::unordered_map<types::Symbol, types::Numeral>& variables) const override final {
        return kValue;    
    }
};

/**
 * @class ENode
 * 
 * @brief Class for the constant e (2.718281828...)
 */
class ENode : public NullaryNode {
private:
    static constexpr types::Numeral kValue = 2.71828182845904532;

public:
    /**
     * @brief Default constructor.
     */
    ENode() : NullaryNode() {}

    virtual types::Numeral evaluate(const SymbolTable& symbols) const override final { return kValue; }

    virtual types::Numeral evaluateAt(const SymbolTable& symbols, 
        const std::unordered_map<types::Symbol, types::Numeral>& variables) const override final {
        return kValue;    
    }
};

/**
 * @class AdditionNode
 * 
 * @brief Binary node of the addition operation.
 */
class AdditionNode : public BinaryNode {
public:
    /**
     * @brief Default constructor.
     */
    AdditionNode() : BinaryNode() {}

    /**
     * @brief Constructor of the AdditionNode.
     * 
     * @param left rvalue reference to a std::unique_ptr to its left children
     * @param right rvalue reference to a std::unique_ptr to its right children
     */
    AdditionNode(std::unique_ptr<ExprNode>&& left, std::unique_ptr<ExprNode>&& right) : BinaryNode(std::move(left), std::move(right)) {}
    
    virtual types::Numeral evaluate(const SymbolTable& symbols) const override final { 
        return left_->evaluate(symbols) + right_->evaluate(symbols);
    }

    virtual types::Numeral evaluateAt(const SymbolTable& symbols, 
        const std::unordered_map<types::Symbol, types::Numeral>& variables) const override final {
        return left_->evaluateAt(symbols, variables) + right_->evaluateAt(symbols, variables);   
    }
};

/**
 * @class SubtractionNode
 * 
 * @brief Binary node of the subtraction operation.
 */
class SubtractionNode : public BinaryNode {
public:
    /**
     * @brief Default constructor.
     */
    SubtractionNode() : BinaryNode() {}

    /**
     * @brief Constructor of the AdditionNode.
     * 
     * @param left rvalue reference to a std::unique_ptr to its left children
     * @param right rvalue reference to a std::unique_ptr to its right children
     */
    SubtractionNode(std::unique_ptr<ExprNode>&& left, std::unique_ptr<ExprNode>&& right) : BinaryNode(std::move(left), std::move(right)) {}
    
    virtual types::Numeral evaluate(const SymbolTable& symbols) const override final { 
        return left_->evaluate(symbols) - right_->evaluate(symbols);
    }

    virtual types::Numeral evaluateAt(const SymbolTable& symbols, 
        const std::unordered_map<types::Symbol, types::Numeral>& variables) const override final {
        return left_->evaluateAt(symbols, variables) - right_->evaluateAt(symbols, variables);   
    }
};

/**
 * @class MultiplicationNode
 * 
 * @brief Binary node of the multiplication operation.
 */
class MultiplicationNode : public BinaryNode {
public:
    /**
     * @brief Default constructor.
     */
    MultiplicationNode() : BinaryNode() {}

    /**
     * @brief Constructor of the AdditionNode.
     * 
     * @param left rvalue reference to a std::unique_ptr to its left children
     * @param right rvalue reference to a std::unique_ptr to its right children
     */
    MultiplicationNode(std::unique_ptr<ExprNode>&& left, std::unique_ptr<ExprNode>&& right) : BinaryNode(std::move(left), std::move(right)) {}
    
    virtual types::Numeral evaluate(const SymbolTable& symbols) const override final { 
        return left_->evaluate(symbols) * right_->evaluate(symbols);
    }

    virtual types::Numeral evaluateAt(const SymbolTable& symbols, 
        const std::unordered_map<types::Symbol, types::Numeral>& variables) const override final {
        return left_->evaluateAt(symbols, variables) * right_->evaluateAt(symbols, variables);   
    }
};

/**
 * @class DivisionNode
 * 
 * @brief Binary node of the division operation.
 */
class DivisionNode : public BinaryNode {
public:
    /**
     * @brief Default constructor.
     */
    DivisionNode() : BinaryNode() {}

    /**
     * @brief Constructor of the AdditionNode.
     * 
     * @param left rvalue reference to a std::unique_ptr to its left children
     * @param right rvalue reference to a std::unique_ptr to its right children
     */
    DivisionNode(std::unique_ptr<ExprNode>&& left, std::unique_ptr<ExprNode>&& right) : BinaryNode(std::move(left), std::move(right)) {}
    
    /**
     * @throws std::runtime_error if attempts to divide by 0
     */
    virtual types::Numeral evaluate(const SymbolTable& symbols) const override final { 
        auto right_result = right_->evaluate(symbols);
        if (right_result == 0) throw std::runtime_error("Numerical error: Cannot divide by 0"); // Cannot divide by zero
        return left_->evaluate(symbols) / right_result;
    }

    /**
     * @throws std::runtime_error if attempts to divide by 0
     */
    virtual types::Numeral evaluateAt(const SymbolTable& symbols, 
        const std::unordered_map<types::Symbol, types::Numeral>& variables) const override final {
        auto right_result = right_->evaluateAt(symbols, variables);
        if (right_result == 0) throw std::runtime_error("Numerical error: Cannot divide by 0"); // Cannot divide by zero
        return left_->evaluateAt(symbols, variables) / right_result;
    }
};

} // namespace expr
