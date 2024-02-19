#include "while_statement.h"

#include <iostream>

namespace ctjs::ast {
WhileStatement::WhileStatement(std::string file_name, SourceLocation loc,
                               std::shared_ptr<Expression> condition,
                               std::shared_ptr<Statement> body)
    : file_name_(file_name), loc_(loc), condition_(condition), body_(body) {}

void WhileStatement::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "WhileStatement(\n";
  condition_->to_string(indent + 2);
  std::cout << ",\n";
  body_->to_string(indent + 2);
  std::cout << "\n" << std::string(indent, ' ') << ")";
}

auto WhileStatement::evaluate(std::shared_ptr<Environment> environment)
    -> Value {
  while (condition_->evaluate(environment).coerce<bool>()) {
    body_->evaluate(environment);
  }
  return Value();
}
}  // namespace ctjs::ast
