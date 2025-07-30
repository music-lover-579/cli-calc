#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>
#include "data/datatype_decl.h"

/**
 * @class SymbolTable
 * 
 * @brief Class for the symbol table.
 */
template<typename T>
class SymbolTable {
private:
    std::unordered_map<std::string, T> symbols_;

public:
    /**
     * @brief Adds a symbol to the symbol list.
     * 
     * @param symbol_name name of the symbol
     * @param value value of the symbol (default value 0)
     * @returns A reference to this
     */
    SymbolTable& insert_or_assign(const std::string& symbol_name, const T& value = 0);

    /**
     * @brief Checks whether a symbol exists in the symbol table.
     * 
     * @param symbol_name name of the symbol to check
     */
    bool contains(const std::string& symbol_name) const noexcept;

    /**
     * @brief Acquires the value of a symbol in the symbol table.
     * 
     * @param symbol_name name of the symbol to get the value
     * @throws A std::runtime_error if symbol_name does not exist
     */
    const T& at(const std::string& symbol_name) const;

    /**
     * @brief Overload the [] operator for access to data members.
     * 
     * @param symbol_name the name of the symbol
     * @note Will default-initialize the value if symbol_name does not currently exist.
     */
    T& operator[](const std::string& symbol_name);
};
