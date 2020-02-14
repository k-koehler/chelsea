#ifndef LEX_HPP
#define LEX_HPP

#include <string>
#include <vector>

enum FirstPassTokenType {
  LPAREN = 0,
  RPAREN,
  PLUS,
  MINUS,
  ASTERISK,
  DIV,
  MOD,
  ASSIGN,
  LITERAL,
  IDENTIFIER,
  KEYWORD,
  SEPARATOR,
};

struct FirstPassToken {
  const FirstPassTokenType type;
  const std::string value;
};

struct LexingError {
  const int index;
  const char symbol;
};

std::vector<FirstPassToken> first_pass_lex(const std::string &);

#endif // LEX_HPP
