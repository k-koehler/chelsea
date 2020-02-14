#ifndef PARSE_HPP
#define PARSE_HPP

#include "../lex/lex.hpp"

#include <vector>

enum Symbol {
    lparen,
    rparen,
    add,
    sub,
    mul,
    divide,
    mod,
    constant,
    mut,
    var,
    identifier,
    int64_literal,
};

void parse(const std::vector<Token> &);

#endif  // PARSE_HPP
