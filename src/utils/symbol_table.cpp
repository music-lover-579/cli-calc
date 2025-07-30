#include "utils/symbol_table.h"

template<typename T>
SymbolTable<T>& SymbolTable<T>::insert_or_assign(const std::string& symbol_name, const T& value) {
    symbols_.insert_or_assign(symbol_name, value);
    return *this;
}

template<typename T>
bool SymbolTable<T>::contains(const std::string& symbol_name) const noexcept {
    return (symbols_.find(symbol_name) != symbols_.end());
}

template<typename T>
const T& SymbolTable<T>::at(const std::string& symbol_name) const {
    auto it = symbols_.find(symbol_name);
    if (it == symbols_.end()) throw std::runtime_error("Symbol '" + symbol_name + "' undefined");
    return it->second;
}

template<typename T>
T& SymbolTable<T>::operator[](const std::string& symbol_name) {
    return symbols_[symbol_name];
}
