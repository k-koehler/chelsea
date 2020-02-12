#include <iostream>

#include "lex.hpp"

void test_munch_whitespace_space(void);
void test_munch_whitespace_tab(void);
void test_munch_lparen(void);

int main() {
  test_munch_whitespace_space();
  test_munch_lparen();
  std::cout << "Success!" << std::endl;
  return EXIT_SUCCESS;
}

void test_munch_whitespace_space() {
  const std::string src = "      ";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 0);
}

void test_munch_whitespace_tab() {
  const std::string src = "\t\t";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 0);
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
