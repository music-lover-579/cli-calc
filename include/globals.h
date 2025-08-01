#pragma once

#include <getopt.h>
#include <string>
#include <iostream>
#include <stdexcept>

// Define some colors and styles
#define RGB_TEXT(r, g, b) "\033[38;2;"#r";"#g";"#b"m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define RESET "\033[0m"

enum class Mode { Evaluate, Statistics, NumberTheory };

class CliHelp : public std::exception {};
class CliVersion : public std::exception {};

/**
 * @struct CliArgs
 * 
 * @brief Struct containing the parsed command line interface arguments
 */
struct CliArgs {
    Mode mode_;       // Mode to compute
    std::string str_; // String to compute
};

/**
 * @brief Acquires the evaluation string from the command line arguments.
 * 
 * @param argc argc from main()
 * @param argv argv from main()
 * @returns the std::string for the string to evaluate
 * @throws std::invalid_argument if encounters invalid argument
 */
inline CliArgs get_cli_args(int argc, char* argv[]) {
    static struct option long_options[] = {
        {"help",    no_argument,       0, 'h'},
        {"version", no_argument,       0, 'v'},
        {"eval",    required_argument, 0, 'e'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    CliArgs result;
    
    while ((opt = getopt_long(argc, argv, "hve:", long_options, &option_index)) != -1) {
        switch (opt) {
        case 'e':
            result.mode_ = Mode::Evaluate;
            result.str_ = optarg;
            break;
        case 'h':
            throw CliHelp();
        case 'v':
            throw CliVersion();
        case '?': default:
            throw std::invalid_argument("Invalid command line argument");
        }
    }

    return result;
}

/**
 * @brief Displays help.
 */
inline void show_help() {
    // TODO
    std::cout << "cli-calc help" << std::endl;
}

/**
 * @brief Displays version.
 */
inline void show_version() {
    std::cout << "cli-calc version 0.1" << std::endl;
}

