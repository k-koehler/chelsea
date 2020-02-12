#ifndef LEX_HPP
#define LEX_HPP

#include <iostream>
#include <string>
#include <vector>

enum TokenType {
  LPAREN = 0,
  RPAREN,
  BINOP_ADD,
  BINOP_MUL,
  BINOP_DIV,
  BINOP_MOD,
  OP_INCR,
  OP_DECR,
  OP_ASSIGN,
  INT_8_LITERAL,
  INT_16_LITERAL,
  INT_32_LITERAL,
  INT_64_LITERAL,
  KEYWORD_CONST,
  KEYWORD_MUT,
  KEYWORD_VAR,
};

struct Token {
  const TokenType type;
  const std::string value;
};

std::vector<Token> lex(const std::string &);

#endif // LEX_HPP
