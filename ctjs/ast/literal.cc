#include "literal.h"

#include <iostream>

namespace ctjs::ast {
Literal::Literal(std::string file_name, SourceLocation loc, int value)
    : file_name_(file_name), loc_(loc), value_(value) {}

void Literal::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "Literal(" << value_ << ")";
}
auto Literal::evaluate([[maybe_unused]] Environment& environment) -> Value {
  return Value(value_);
}
}  // namespace ctjs::ast
