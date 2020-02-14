#include <cassert>
#include <iostream>

#include "lex.hpp"

void test_munch_unexpected_symbol() {
    const std::string src = "\\";
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
        assert(tok.type == PLUS);
        assert(tok.value == std::string("+"));
    }
}

//// TODO --
void test_munch_binop_sub() {
    const std::string src = "--";
    const std::vector<Token> tokens = lex(src);
    assert(tokens.size() == 2);
    for (const auto &tok : tokens) {
        assert(tok.type == MINUS);
        assert(tok.value == std::string("-"));
    }
}

// TODO pointer, *=
void test_munch_binop_mul() {
    const std::string src = "**";
    const std::vector<Token> tokens = lex(src);
    assert(tokens.size() == 2);
    for (const auto &tok : tokens) {
        assert(tok.type == ASTERISK);
        assert(tok.value == std::string("*"));
    }
}

// TODO /=
void test_munch_binop_div() {
    const std::string src = "//";
    const std::vector<Token> tokens = lex(src);
    assert(tokens.size() == 2);
    for (const auto &tok : tokens) {
        assert(tok.type == DIV);
        assert(tok.value == std::string("/"));
    }
}

void test_munch_binop_mod() {
    const std::string src = "%%";
    const std::vector<Token> tokens = lex(src);
    assert(tokens.size() == 2);
    for (const auto &tok : tokens) {
        assert(tok.type == MOD);
        assert(tok.value == std::string("%"));
    }
}

// TODO ==
void test_munch_binop_assign() {
    const std::string src = "==";
    const std::vector<Token> tokens = lex(src);
    assert(tokens.size() == 2);
    for (const auto &tok : tokens) {
        assert(tok.type == ASSIGN);
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

void test_munch_identifier() {
    const std::string src = "identifier1 _identifier2";
    const std::vector<Token> tokens = lex(src);
    assert(tokens.size() == 2);
    assert(tokens[0].value == std::string("identifier1"));
    assert(tokens[0].type == IDENTIFIER);
    assert(tokens[1].value == std::string("_identifier2"));
    assert(tokens[1].type == IDENTIFIER);
}

void test_munch_basic_digit() {
    const std::string src = "328329 234234";
    const std::vector<Token> tokens = lex(src);
    assert(tokens.size() == 2);
    assert(tokens[0].value == std::string("328329"));
    assert(tokens[0].type == LITERAL);
    assert(tokens[1].value == std::string("234234"));
    assert(tokens[1].type == LITERAL);
}

void test_munch_various_first_pass_tokens_1() {
    const std::string src = "const var foo = 10;";
    const auto tokens = lex(src);
    assert(tokens[0].type == IDENTIFIER);
    assert(tokens[0].value == std::string("const"));
    assert(tokens[1].type == IDENTIFIER);
    assert(tokens[1].value == std::string("var"));
    assert(tokens[2].type == IDENTIFIER);
    assert(tokens[2].value == std::string("foo"));
    assert(tokens[3].type == ASSIGN);
    assert(tokens[3].value == std::string("="));
    assert(tokens[4].type == LITERAL);
    assert(tokens[4].value == std::string("10"));
    assert(tokens[5].type == SEPARATOR);
    assert(tokens[5].value == std::string(";"));
}

void test_munch_various_first_pass_tokens_2() {
    const std::string src = "const \t var _10 = (5 +\n5);";
    const auto tokens = lex(src);
    assert(tokens[0].type == IDENTIFIER);
    assert(tokens[0].value == std::string("const"));
    assert(tokens[1].type == IDENTIFIER);
    assert(tokens[1].value == std::string("var"));
    assert(tokens[2].type == IDENTIFIER);
    assert(tokens[2].value == std::string("_10"));
    assert(tokens[3].type == ASSIGN);
    assert(tokens[3].value == std::string("="));
    assert(tokens[4].type == LPAREN);
    assert(tokens[4].value == std::string("("));
    assert(tokens[5].type == LITERAL);
    assert(tokens[5].value == std::string("5"));
    assert(tokens[6].type == PLUS);
    assert(tokens[6].value == std::string("+"));
    assert(tokens[7].type == LITERAL);
    assert(tokens[7].value == std::string("5"));
    assert(tokens[8].type == RPAREN);
    assert(tokens[8].value == std::string(")"));
    assert(tokens[9].type == SEPARATOR);
    assert(tokens[9].value == std::string(";"));
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
    test_munch_identifier();
    test_munch_basic_digit();
    test_munch_various_first_pass_tokens_1();
    test_munch_various_first_pass_tokens_2();
    std::cout << "Success!" << std::endl;
    return EXIT_SUCCESS;
}
