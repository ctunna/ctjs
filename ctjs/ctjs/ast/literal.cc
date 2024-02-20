#include "ctjs/ast/literal.h"

#include <iostream>

namespace ctjs::ast {
Literal::Literal(std::string file_name, SourceLocation loc, Value value)
    : file_name_(file_name), loc_(loc), value_(value) {}

void Literal::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "Literal(" << value_.to_string()
            << ")";
}
auto Literal::evaluate(
    [[maybe_unused]] std::shared_ptr<Environment> environment) -> Value {
  return value_;
}
}  // namespace ctjs::ast
