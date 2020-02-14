#include <iostream>

#include "lex/lex.hpp"

const std::string src = "hello";

int main() {
  first_pass_lex(src);
  return EXIT_SUCCESS;
}