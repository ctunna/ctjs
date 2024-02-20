#include "ctjs/ast/variable_declaration.h"

#include <iostream>

namespace ctjs::ast {
VariableDeclaration::VariableDeclaration(
    std::string file_name, SourceLocation loc,
    std::vector<std::shared_ptr<VariableDeclarator>> declarations)
    : file_name_(file_name), loc_(loc), declarations_(declarations) {}

void VariableDeclaration::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "VariableDeclaration([";
  for (auto &decl : declarations_) {
    std::cout << "\n";
    decl->to_string(indent + 2);
    std::cout << "\n";
  }
  std::cout << std::string(indent, ' ') << "])";
}

auto VariableDeclaration::evaluate(std::shared_ptr<Environment> environment)
    -> Value {
  for (auto &decl : declarations_) {
    decl->evaluate(environment);
  }
  return Value();
}
}  // namespace ctjs::ast
