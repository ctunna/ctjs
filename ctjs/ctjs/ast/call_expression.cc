#include "ctjs/ast/call_expression.h"

#include <iostream>

#include "ctjs/ast/return_exception.h"
#include "ctjs/runtime/function.h"

namespace ctjs::ast {
CallExpression::CallExpression(
    std::string file_name, SourceLocation loc,
    std::shared_ptr<Expression> callee,
    std::vector<std::shared_ptr<Expression>> arguments)
    : file_name_(file_name),
      loc_(loc),
      callee_(callee),
      arguments_(arguments) {}

void CallExpression::to_string(int indent) {
  std::cout << std::string(indent, ' ') << "CallExpression(\n";
  callee_->to_string(indent + 2);
  std::cout << ",\n";
  for (auto& arg : arguments_) {
    arg->to_string(indent + 2);
    std::cout << ",\n";
  }
  std::cout << std::string(indent, ' ') << ")";
}

auto CallExpression::evaluate(std::shared_ptr<Environment> environment)
    -> Value {
  auto callee{callee_->evaluate(environment).coerce<Function>()};
  std::vector<Value> args;
  for (auto& arg : arguments_) {
    args.push_back(arg->evaluate(environment));
  }
  try {
    return callee.call(args);
  } catch (ReturnException& e) {
    return e.value();
  }
}
}  // namespace ctjs::ast
