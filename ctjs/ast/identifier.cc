#include "identifier.h"

#include <iostream>

namespace ctjs::ast {
Identifier::Identifier(std::string file_name, SourceLocation loc,
                       std::string name)
    : file_name_(file_name), loc_(loc), name_(name) {}

void Identifier::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "Identifier(" << name_ << ")";
}

auto Identifier::evaluate(std::shared_ptr<Environment> environment) -> Value {
  return environment->get(name_);
}

auto Identifier::name() const -> std::string { return name_; }
}  // namespace ctjs::ast
