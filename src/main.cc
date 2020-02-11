#include <iostream>

#include "lex/lex.hpp"

const std::string src = "hello";

int main() {
  lex(src);
  return EXIT_SUCCESS;
}