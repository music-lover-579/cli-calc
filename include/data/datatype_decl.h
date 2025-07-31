#pragma once

#include <string>
#include <variant>
#include <stdexcept>
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
inline Numeral string_to_numeral(const std::string& str) { 
    // Checks whether there are multiple decimal points
    bool has_decimal = false;
    for (const auto& ch : str) {
        if (ch == '.') {
            if (has_decimal) throw std::runtime_error("Numerical error: '" + str + "' is not a valid number");
            has_decimal = true;
        }
    }
    return std::stod(str); 
}

} // namespace types
