#ifndef AST_H
#define AST_H

#include <memory>
#include <string>

#include "parse.hpp"

struct AstNode {
  const Symbol symbol;
  std::unique_ptr<AstNode> left;
  std::unique_ptr<AstNode> right;

  void add_left(const Symbol);
  void add_right(const Symbol);

  const std::string to_string();

  static std::unique_ptr<AstNode> make(const Symbol);
};

#endif // AST_H