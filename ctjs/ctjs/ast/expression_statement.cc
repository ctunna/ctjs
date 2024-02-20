#include "ctjs/ast/expression_statement.h"

#include <iostream>

namespace ctjs::ast {
ExpressionStatement::ExpressionStatement(std::string file_name,
                                         SourceLocation loc,
                                         std::shared_ptr<Expression> expression)
    : expression_(expression), file_name_(file_name), loc_(loc) {}

void ExpressionStatement::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "ExpressionStatement(\n";
  expression_->to_string(indent + 2);
  std::cout << "\n" << std::string(indent, ' ') << ")";
}

auto ExpressionStatement::evaluate(std::shared_ptr<Environment> environment) -> Value {
  return expression_->evaluate(environment);
}

}  // namespace ctjs::ast
