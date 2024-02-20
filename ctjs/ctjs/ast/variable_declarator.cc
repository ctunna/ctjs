#include "ctjs/ast/variable_declarator.h"

#include <iostream>

namespace ctjs::ast {
VariableDeclarator::VariableDeclarator(std::string file_name,
                                       SourceLocation loc,
                                       std::shared_ptr<Identifier> id,
                                       std::shared_ptr<Expression> init)
    : file_name_(file_name), loc_(loc), id_(id), init_(init) {}

void VariableDeclarator::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "VariableDeclarator(";
  std::cout << "\n";
  id_->to_string(indent + 2);
  std::cout << ", ";
  std::cout << "\n";
  init_->to_string(indent + 2);
  std::cout << "\n" << std::string(indent, ' ') << ")";
}

auto VariableDeclarator::evaluate(std::shared_ptr<Environment> environment) -> Value {
  auto value{init_->evaluate(environment)};
  environment->set(id_->name(), init_->evaluate(environment));
  return value;
}
}  // namespace ctjs::ast
