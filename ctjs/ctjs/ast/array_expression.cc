#include "ctjs/ast/array_expression.h"

#include <iostream>

namespace ctjs::ast {
ArrayExpression::ArrayExpression(
    std::string file_name, SourceLocation loc,
    std::vector<std::shared_ptr<Expression>> elements)
    : file_name_(file_name), loc_(loc), elements_(elements) {}

void ArrayExpression::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "ArrayExpression(";
  for (auto const& element : elements_) {
    element->to_string(indent + 2);
    std::cout << "\n";
  }
  std::cout << std::string(indent, ' ') << ")";
}

auto ArrayExpression::evaluate(std::shared_ptr<Environment> environment)
    -> Value {
  std::vector<Value> values;
  for (auto const& element : elements_) {
    values.push_back(element->evaluate(environment));
  }
  return Value();
}

}  // namespace ctjs::ast