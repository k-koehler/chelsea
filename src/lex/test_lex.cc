#include <iostream>

#include "lex.hpp"

void test_munch_unexpected_symbol() {
  const std::string src = "sdfsjkdfjksdfkj";
  bool threw = false;
  try {
    lex(src);
  } catch (LexingError &) {
    threw = true;
  }
  assert(threw == true);
}

void test_munch_whitespace_space() {
  const std::string src = "  ";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 0);
}

void test_munch_whitespace_tab() {
  const std::string src = "\t\t";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 0);
}

void test_munch_whitespace_newline() {
  const std::string src = "\n\n";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 0);
}

void test_munch_lparen() {
  const std::string src = "((";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 2);
  for (const auto &tok : tokens) {
    assert(tok.type == LPAREN);
    assert(tok.value == std::string("("));
  }
}

void test_munch_rparen() {
  const std::string src = "))";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 2);
  for (const auto &tok : tokens) {
    assert(tok.type == RPAREN);
    assert(tok.value == std::string(")"));
  }
}

// TODO ++
void test_munch_binop_plus() {
  const std::string src = "++";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 2);
  for (const auto &tok : tokens) {
    assert(tok.type == BINOP_ADD);
    assert(tok.value == std::string("+"));
  }
}

//// TODO --
void test_munch_binop_sub() {
  const std::string src = "--";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 2);
  for (const auto &tok : tokens) {
    assert(tok.type == BINOP_SUB);
    assert(tok.value == std::string("-"));
  }
}

// TODO pointer, *=
void test_munch_binop_mul() {
  const std::string src = "**";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 2);
  for (const auto &tok : tokens) {
    assert(tok.type == BINOP_MUL);
    assert(tok.value == std::string("*"));
  }
}

// TODO /=
void test_munch_binop_div() {
  const std::string src = "//";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 2);
  for (const auto &tok : tokens) {
    assert(tok.type == BINOP_DIV);
    assert(tok.value == std::string("/"));
  }
}

void test_munch_binop_mod() {
  const std::string src = "%%";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 2);
  for (const auto &tok : tokens) {
    assert(tok.type == BINOP_MOD);
    assert(tok.value == std::string("%"));
  }
}

// TODO ==
void test_munch_binop_assign() {
  const std::string src = "==";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 2);
  for (const auto &tok : tokens) {
    assert(tok.type == BINOP_ASSIGN);
    assert(tok.value == std::string("="));
  }
}

void test_munch_sep() {
  const std::string src = ";;";
  const std::vector<Token> tokens = lex(src);
  assert(tokens.size() == 2);
  for (const auto &tok : tokens) {
    assert(tok.type == SEPARATOR);
    assert(tok.value == std::string(";"));
  }
}

int main() {
  test_munch_unexpected_symbol();
  test_munch_whitespace_space();
  test_munch_whitespace_tab();
  test_munch_whitespace_newline();
  test_munch_lparen();
  test_munch_rparen();
  test_munch_binop_plus();
  test_munch_binop_sub();
  test_munch_binop_mul();
  test_munch_binop_div();
  test_munch_binop_mod();
  test_munch_binop_assign();
  test_munch_sep();
  std::cout << "Success!" << std::endl;
  return EXIT_SUCCESS;
}
