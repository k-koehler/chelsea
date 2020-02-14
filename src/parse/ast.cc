#include "ast.hpp"

using std::unique_ptr;

unique_ptr<AstNode> AstNode::make(const Symbol sym) {
  return std::make_unique<AstNode>((AstNode *)malloc(sizeof(AstNode *)));
}

void AstNode::add_left(const Symbol sym) { this->left = AstNode::make(sym); }
