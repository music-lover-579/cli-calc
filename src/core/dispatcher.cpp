#include "core/dispatcher.h"

dispatcher::Result dispatcher::get_result(Mode mode, const SymbolTable& symbols,
    std::vector<parser::Token>::const_iterator tokens_begin, std::vector<parser::Token>::const_iterator tokens_end) {

    switch (mode) {
    case Mode::Evaluate:
        return eval::build_expr_tree(tokens_begin, tokens_end)->evaluate(symbols);
    case Mode::Statistics:
        return types::Numeral(); // TODO
    case Mode::NumberTheory:
        return types::Numeral(); // TODO
    default:
        return types::Numeral();
    } // switch (mode)
}
