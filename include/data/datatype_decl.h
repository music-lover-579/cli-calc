#pragma once

#include <string>
#include <variant>
#include "data/big_decimal.h"

namespace types {

typedef double Numeral;
typedef std::string Symbol;
typedef std::variant<Numeral, Symbol> Parameter;

/**
 * @brief Converts a string to a numeral.
 * 
 * @param str string of the numeral
 */
inline Numeral string_to_numeral(const std::string& str) { return std::stod(str); }

} // namespace types
