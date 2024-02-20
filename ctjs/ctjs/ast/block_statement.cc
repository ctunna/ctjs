#include "ctjs/ast/block_statement.h"

#include <iostream>

namespace ctjs::ast {
BlockStatement::BlockStatement(std::string file_name, SourceLocation loc,
                               std::vector<std::shared_ptr<Statement>> body)
    : file_name_(file_name), loc_(loc), body_(body) {}

void BlockStatement::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "BlockStatement([\n";
  for (auto& statement : body_) {
    statement->to_string(indent + 2);
    std::cout << "\n";
  }
  std::cout << std::string(indent, ' ') << "])";
}

auto BlockStatement::evaluate(std::shared_ptr<Environment> environment)
    -> Value {
  for (auto& statement : body_) {
    statement->evaluate(environment);
  }
  return Value();
}
}  // namespace ctjs::ast
