#pragma once

#include <vector>
#include <memory>
#include "data/datatype_decl.h"
#include "utils/symbol_table.h"

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
    virtual types::DataType evaluate(const SymbolTable<types::DataType>& symbols) const = 0; // Purely virtual
    virtual ~ExprNode() = default;

    // Delete copy constructors, default move constructors
    ExprNode(const ExprNode& other) = delete;
    ExprNode& operator=(const ExprNode& other) = delete;
    ExprNode(ExprNode&& other) = default;
    ExprNode& operator=(ExprNode&& other) = default;
};
