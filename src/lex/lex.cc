#include <cctype>
#include <iostream>
#include <stdexcept>

#include "lex.hpp"

using std::size_t;
using std::string;
using std::vector;

static inline bool is_whitespace(const char c) {
    return std::iswspace(static_cast<wint_t>(c));
}
static inline bool is_identifier(const char c) {
    return std::isalnum(c) || c == '_';
}
static inline bool is_digit(const char c) {
    return static_cast<bool>(std::isdigit(c));
}

static inline string iterate_src(const size_t start_index, const string &src,
                                 bool (*evaluate)(const char)) {
    // already checked index 0
    size_t idx, offset = 1;
    for (; (idx = start_index + offset) < src.length() && evaluate(src.at(idx));
         ++offset)
        ;
    return src.substr(start_index, offset);
}

static inline size_t munch_whitespace(const size_t start_index,
                                      const string &src) {
    return iterate_src(start_index, src, is_whitespace).size();
}

static inline size_t munch_identifier(const size_t start_index,
                                      const string &src, vector<Token> &vec) {
    const auto value = iterate_src(start_index, src, is_identifier);
    const struct Token tok = {.type = IDENTIFIER, .value = value};
    vec.push_back(tok);
    return value.size();
}

static inline size_t munch_basic_digit(const size_t start_index,
                                       const string &src, vector<Token> &vec) {
    const auto value = iterate_src(start_index, src, is_digit);
    const struct Token tok = {.type = LITERAL, .value = value};
    vec.push_back(tok);
    return value.size();
}

static inline size_t munch_single(const char symbol, vector<Token> &vec,
                                  const TokenType token_type) {
    const struct Token tok = {.type = token_type, .value = string(1, symbol)};
    vec.push_back(tok);
    return 1;
}

[[noreturn]] static inline void unexpected_symbol(int index,
                                                  const char symbol) {
    const struct LexingError err = {.index = index, .symbol = symbol};
    throw err;
}

vector<Token> lex(const string &src) {
    vector<Token> vec;
    for (size_t index = 0; index < src.length();) {
        const char current_char = src[index];
        if (std::isspace(current_char)) {
            index += munch_whitespace(index, src);
            continue;
        }
        if (std::isdigit(current_char)) {
            index += munch_basic_digit(index, src, vec);
            continue;
        }
        if (std::isalpha(current_char) || current_char == '_') {
            index += munch_identifier(index, src, vec);
            continue;
        }
        switch (current_char) {
            case '(':
                index += munch_single(current_char, vec, LPAREN);
                break;
            case ')':
                index += munch_single(current_char, vec, RPAREN);
                break;
            case '+':
                index += munch_single(current_char, vec, PLUS);
                break;
            case '-':
                index += munch_single(current_char, vec, MINUS);
                break;
            case '*':
                index += munch_single(current_char, vec, ASTERISK);
                break;
            case '/':
                index += munch_single(current_char, vec, DIV);
                break;
            case '%':
                index += munch_single(current_char, vec, MOD);
                break;
            case '=':
                index += munch_single(current_char, vec, ASSIGN);
                break;
            case ';':
                index += munch_single(current_char, vec, SEPARATOR);
                break;
            default:
                unexpected_symbol(static_cast<int>(index), current_char);
        }
    }
    return vec;
}
