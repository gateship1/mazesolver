#ifndef TOKENIZE_HEADER_FILE
#define TOKENIZE_HEADER_FILE

#include <sstream> // std::sstream
#include <vector> // std::vector

/* tokenize
  
  lambda to tokenize a input string based on a given input delimeter
  
  parameters:
    str, string to tokenize
    delimeter, delimeter to tokenize the string on
  
  return
    tokens, the string tokens in a list of strings
*/
auto constexpr tokenize = [](const std::string& str, const char& delimeter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream token_stream(str);
    while (std::getline(token_stream, token, delimeter)) {
        tokens.emplace_back(token);
    }
    return tokens;
};

#endif // TOKENIZE_HEADER_FILE