#include "ctjs/ast/assignment_expression.h"

#include <iostream>

#include "ctjs/ast/identifier.h"

namespace ctjs::ast {
AssignmentExpression::AssignmentExpression(std::string file_name,
                                           SourceLocation loc,
                                           std::shared_ptr<Expression> left,
                                           std::shared_ptr<Expression> right)
    : file_name_(file_name), loc_(loc), left_(left), right_(right) {}

void AssignmentExpression::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "AssignmentExpression(";
  std::cout << "\n";
  left_->to_string(indent + 2);
  std::cout << ", ";
  std::cout << "\n";
  right_->to_string(indent + 2);
  std::cout << "\n" << std::string(indent, ' ') << ")";
}

auto AssignmentExpression::evaluate(std::shared_ptr<Environment> environment)
    -> Value {
  auto value{right_->evaluate(environment)};
  environment->set(std::dynamic_pointer_cast<Identifier>(left_)->name(), value);
  return value;
}
}  // namespace ctjs::ast
