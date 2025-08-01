#pragma once

#include <variant>
#include "globals.h"
#include "data/datatype_decl.h"
#include "core/eval.h"
#include "core/parser.h"
#include "utils/expr_node.h"
#include "utils/operator_table.h"
#include "utils/symbol_table.h"

namespace dispatcher {

typedef std::variant<types::Numeral> Result;

/**
 * @brief Acquires the result from the tokens with the given mode.
 * 
 * @param mode a Mode enum for the mode of calculation
 * @param symbols a SymbolTable for the variables
 * @param tokens_begin an iterator to the begin of a token vector
 * @param tokens_end an iterator to the end of a token vector
 * @returns a Result for the result of calculation
 */
Result get_result(Mode mode, const SymbolTable& symbols,
        std::vector<parser::Token>::const_iterator tokens_begin, std::vector<parser::Token>::const_iterator tokens_end);

} // namespace dispatcher
