#ifndef LEX_HPP
#define LEX_HPP

#include <string>
#include <vector>

enum TokenType {
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

struct Token {
    const TokenType type;
    const std::string value;
};

struct LexingError {
    const int index;
    const char symbol;
};

std::vector<Token> lex(const std::string &);

#endif  // LEX_HPP
