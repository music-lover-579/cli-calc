#include "utils/symbol_table.h"

SymbolTable::SymbolTable() : symbols_() {}

SymbolTable::SymbolTable(const std::unordered_map<types::Symbol, types::Numeral>& symbols) : symbols_(symbols) {}

SymbolTable::SymbolTable(std::initializer_list<std::pair<const types::Symbol, types::Numeral>> items) : symbols_(items) {}

SymbolTable& SymbolTable::insert_or_assign(const types::Symbol& symbol_name, const types::Numeral& value) {
    symbols_.insert_or_assign(symbol_name, value);
    return *this;
}

bool SymbolTable::contains(const types::Symbol& symbol_name) const noexcept {
    return (symbols_.find(symbol_name) != symbols_.end());
}

const types::Numeral& SymbolTable::at(const types::Symbol& symbol_name) const {
    auto it = symbols_.find(symbol_name);
    if (it == symbols_.end()) throw std::runtime_error("Syntax error: Symbol '" + symbol_name + "' undefined");
    return it->second;
}

types::Numeral& SymbolTable::operator[](const types::Symbol& symbol_name) {
    return symbols_[symbol_name];
}
