#include <cctype>
#include <stdexcept>

#include "lex.hpp"

using std::string;
using std::vector;

static inline int munch_whitespace(int cur_index, const string &src) {
  int idx, offset = 0;
  while ((idx = cur_index + (offset++)) < src.length() &&
         std::iswspace(src.at(idx)))
    ;
  return offset;
}

static inline int munch_single(const char symbol, vector<Token> &vec,
                               const TokenType token_type) {
  const struct Token tok = {.type = token_type, .value = string(1, symbol)};
  vec.push_back(tok);
  return 1;
}

static inline void unexpected_symbol(int index, const char symbol) {
  const struct LexingError err = {.index = index, .symbol = symbol};
  throw err;
}

vector<Token> lex(const string &src) {
  vector<Token> vec;
  for (int index = 0; index < src.length();) {
    const char current_char = src[index];
    if (std::isspace(current_char)) {
      index += munch_whitespace(index, src);
      continue;
    }
    switch (current_char) {
    case '(':
      index += munch_single(current_char, vec, LPAREN);
      break;
    default:
      unexpected_symbol(index, current_char);
    }
  }
  return vec;
}
