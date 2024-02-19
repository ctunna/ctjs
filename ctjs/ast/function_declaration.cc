#include "function_declaration.h"

#include <iostream>

#include "../function.h"

namespace ctjs::ast {
FunctionDeclaration::FunctionDeclaration(
    std::string file_name, SourceLocation loc, std::shared_ptr<Identifier> id,
    std::vector<std::shared_ptr<Identifier>> params,
    std::shared_ptr<BlockStatement> body)
    : file_name_(file_name), loc_(loc), id_(id), params_(params), body_(body) {}

void FunctionDeclaration::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "FunctionDeclaration(\n";
  id_->to_string(indent + 2);
  std::cout << "\n";
  for (auto const &param : params_) {
    param->to_string(indent + 2);
    std::cout << "\n";
  }
  body_->to_string(indent + 2);
  std::cout << "\n" << std::string(indent, ' ') << ")";
}

auto FunctionDeclaration::evaluate(std::shared_ptr<Environment> environment)
    -> Value {
  Function function{weak_from_this(), environment};
  environment->set(id_->name(), function);
  return function;
}
}  // namespace ctjs::ast
