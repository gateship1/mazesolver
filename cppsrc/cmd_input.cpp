#include "cmd_input.hpp"

/* build_arg_str
  
  build a single continuous string from the command line arguments.
  this string is to be passed into the tokenizer for special parsing
  
  parameters:
    argc, number of command line arguments
    argv, list of command line arguments (c style array of char arrays)
  
  return:
    a string of the flags-value command line pairs
*/
auto build_arg_str(const int& argc, char** argv) -> std::string {
    std::string arg_str;
    for (int arg{1}; arg < argc; ++arg) {
        arg_str = arg_str + tokenize(argv[arg],'-').back() + " ";
    }
    return arg_str;
}

/* cmd_option_exists
  
  checks to see if the input command line argument (option) exists
  
  parameters:
    begin, first argument in the c style array of char arrays
    end, last argument in the c style array of char arrays
    option, the argument for which to search
  
  return:
    true if the option exits, false otherwis
*/
auto cmd_option_exists(char** begin, char** end, const std::string& option) -> bool {
    auto itr{std::find(begin, end, option)};
    auto exists{itr != end};
    std::cout << **itr + 0 << '\n';
    return exists;
}