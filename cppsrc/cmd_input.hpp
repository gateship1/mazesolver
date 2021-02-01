#ifndef CMD_INPUT_HEADER_FILE
#define CMD_INPUT_HEADER_FILE

#include <algorithm>
#include <iostream>
#include <string>

#include "tokenize.hpp"

auto build_arg_str(const int&, char**) -> std::string;
auto cmd_option_exists(char**, char**, const std::string&) -> bool;

#endif // CMD_INPUT_HEADER_FILE