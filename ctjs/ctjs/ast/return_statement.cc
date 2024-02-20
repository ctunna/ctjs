#include "ctjs/ast/return_statement.h"

#include <iostream>

#include "ctjs/ast/return_exception.h"

namespace ctjs::ast {
ReturnStatement::ReturnStatement(std::string file_name, SourceLocation loc,
                                 std::shared_ptr<Expression> argument)
    : file_name_(file_name), loc_(loc), argument_(argument) {}

void ReturnStatement::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "ReturnStatement(\n";
  if (argument_) {
    argument_->to_string(indent + 2);
  } else {
    std::cout << std::string(indent + 2, ' ') << "null\n";
  }
  std::cout << "\n" << std::string(indent, ' ') << ")";
}

auto ReturnStatement::evaluate(std::shared_ptr<Environment> environment)
    -> Value {
  auto value{argument_->evaluate(environment)};
  throw ReturnException(value);
}
}  // namespace ctjs::ast