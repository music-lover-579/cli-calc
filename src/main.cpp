#include <iostream>
#include "globals.h"
#include "core/dispatcher.h"
#include "core/parser.h"

int main(int argc, char* argv[]) {
    if (argc > 1) { // There are some command-line options
        try {
            CliArgs args = get_cli_args(argc, argv);
            auto tokens = parser::tokenize(args.str_);
            dispatcher::Result result = dispatcher::get_result(args.mode_, {}, tokens.begin(), tokens.end());
            if (std::holds_alternative<types::Numeral>(result)) {
                std::cout << "\nans = " << std::get<types::Numeral>(result) << "\n" << std::endl;
            }
        }
        catch (const CliHelp&) {
            show_help();
            return 0;
        }
        catch (const CliVersion&) {
            show_version();
            return 0;
        }
        catch (const std::invalid_argument& err) {
            std::cerr << err.what() << std::endl;
            return 1;
        }
        catch (const std::runtime_error& err) {
            std::cerr << err.what() << std::endl;
            return 1;
        }
        catch (...) {
            std::cerr << "Internal error" << std::endl;
            return 1;
        }
    }
    else {
        // TODO, enter cycle (somewhat like a shell)
        std::cout << "Hello, world!" << std::endl;
    }
    return 0;
}
