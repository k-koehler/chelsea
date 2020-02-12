#include "lex.hpp"

void test_munch_lparen(void);

int main() {
  test_munch_lparen();
  std::cout << "Success!";
  return EXIT_SUCCESS;
}

void test_munch_lparen() {
  const std::string src = "(((";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 3);
  for (const auto &tok : tokens) {
    assert(tok.type == LPAREN);
    assert(tok.value == std::string("("));
  }
}
