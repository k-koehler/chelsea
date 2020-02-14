#include <iostream>

#include "lex/lex.hpp"

const std::string src = "hello";

int main() {
    const auto tokens = lex(src);
    return EXIT_SUCCESS;
}