#pragma once

#include <string>
#include <variant>
#include "data/big_decimal.h"

namespace types {
    typedef double Numeral;
    typedef std::string Symbol;
    typedef std::variant<Numeral, Symbol> Parameter;
}
