#include "program.h"

#include <iostream>

namespace ctjs::ast {
Program::Program(std::string file_name, SourceLocation loc,
                 std::vector<std::shared_ptr<Statement>> body)
    : file_name_(file_name), loc_(loc), body_(body) {}

void Program::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "Program([\n";
  for (auto &stmt : body_) {
    stmt->to_string(indent + 2);
    std::cout << "\n";
  }
  std::cout << "])";
}

auto Program::evaluate(std::shared_ptr<Environment> environment) -> Value {
  for (auto &stmt : body_) {
    stmt->evaluate(environment);
  }
  return Value();
}
}  // namespace ctjs::ast
