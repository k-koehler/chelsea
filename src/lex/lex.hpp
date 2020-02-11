#ifndef LEX_HPP
#define LEX_HPP

#include <iostream>
#include <string>
#include <vector>

struct Token {};

std::vector<Token> lex(const std::string &);

enum TokenType {
  NUMERIC_VALUE,
};

#endif // LEX_HPP
