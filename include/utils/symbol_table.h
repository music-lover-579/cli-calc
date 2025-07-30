#pragma once

#include <string>
#include <initializer_list>
#include <unordered_map>
#include <stdexcept>
#include "data/datatype_decl.h"

/**
 * @class SymbolTable
 * 
 * @brief Class for the symbol table.
 */
class SymbolTable {
private:
    std::unordered_map<types::Symbol, types::Numeral> symbols_;

public:
    /**
     * @brief Default constructor.
     */
    SymbolTable();

    /**
     * @brief Constructor for SymbolTable.
     * 
     * @param symbols an already existing symbol table to call
     */
    SymbolTable(const std::unordered_map<types::Symbol, types::Numeral>& symbols);

    /**
     * @brief Constructor for SymbolTable, using initializer lists.
     * 
     * @param items the initializer list
     */
    SymbolTable(std::initializer_list<std::pair<const types::Symbol, types::Numeral>> items);

    ~SymbolTable() = default;

    /**
     * @brief Adds a symbol to the symbol list.
     * 
     * @param symbol_name name of the symbol
     * @param value value of the symbol (default value 0)
     * @returns A reference to this
     */
    SymbolTable& insert_or_assign(const types::Symbol& symbol_name, const types::Numeral& value = 0);

    /**
     * @brief Checks whether a symbol exists in the symbol table.
     * 
     * @param symbol_name name of the symbol to check
     */
    bool contains(const types::Symbol& symbol_name) const noexcept;

    /**
     * @brief Acquires the value of a symbol in the symbol table.
     * 
     * @param symbol_name name of the symbol to get the value
     * @throws A std::runtime_error if symbol_name does not exist
     */
    const types::Numeral& at(const types::Symbol& symbol_name) const;

    /**
     * @brief Overload the [] operator for access to data members.
     * 
     * @param symbol_name the name of the symbol
     * @note Will default-initialize the value if symbol_name does not currently exist.
     */
    types::Numeral& operator[](const types::Symbol& symbol_name);
};
