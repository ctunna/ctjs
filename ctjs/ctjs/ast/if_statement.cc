#include "ctjs/ast/if_statement.h"

#include <iostream>

namespace ctjs::ast {
IfStatement::IfStatement(std::string file_name, SourceLocation loc,
                         std::shared_ptr<Expression> test,
                         std::shared_ptr<Statement> consequent,
                         std::shared_ptr<Statement> alternate)
    : file_name_(file_name),
      loc_(loc),
      test_(test),
      consequent_(consequent),
      alternate_(alternate) {}

void IfStatement::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "IfStatement(\n";
  test_->to_string(indent + 2);
  std::cout << "\n";
  consequent_->to_string(indent + 2);
  std::cout << "\n";
  if (alternate_) {
    alternate_->to_string(indent + 2);
  } else {
    std::cout << std::string(indent + 2, ' ') << "null";
  }
  std::cout << "\n" << std::string(indent, ' ') << ")";
}

auto IfStatement::evaluate(std::shared_ptr<Environment> environment) -> Value {
  if (test_->evaluate(environment).coerce<bool>()) {
    return consequent_->evaluate(environment);
  } else if (alternate_) {
    return alternate_->evaluate(environment);
  }
  return Value();
}
}  // namespace ctjs::ast
