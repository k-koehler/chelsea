#include "lex.hpp"

using std::string;
using std::vector;

int munch_lparen(int cur_index, const string &src, vector<Token> &vec) {
  struct Token tok = {.type = LPAREN, .value = string(1, src[cur_index])};
  vec.push_back(tok);
  return 1;
}

vector<Token> lex(const string &src) {
  vector<Token> vec;
  for (int i = 0; i < src.length();) {
    switch (src[i]) {
    case '(':
      i += munch_lparen(i, src, vec);
      break;
    default:
      ++i;
      break;
    }
  }
  return vec;
}
