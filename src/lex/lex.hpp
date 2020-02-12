#ifndef LEX_HPP
#define LEX_HPP

#include <string>
#include <vector>

enum TokenType {
  LPAREN = 0,
  RPAREN,
  BINOP_ADD,
  BINOP_SUB,
  BINOP_MUL,
  BINOP_DIV,
  BINOP_MOD,
  BINOP_ASSIGN,
  OP_INCR,
  OP_DECR,
  INT_8_LITERAL,
  INT_16_LITERAL,
  INT_32_LITERAL,
  INT_64_LITERAL,
  KEYWORD_CONST,
  KEYWORD_MUT,
  KEYWORD_VAR,
  SEPARATOR,
};

struct Token {
  const TokenType type;
  const std::string value;
};

struct LexingError {
  const int index;
  const char symbol;
};

std::vector<Token> lex(const std::string &);

#endif // LEX_HPP
