
#include "ctjs/runtime/user_defined_function.h"

#include <variant>

#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"
#include "ctjs/util/box.h"
#include "ctjs/visitor/interpreter_visitor.h"

namespace ctjs {
UserDefinedFunction::UserDefinedFunction(
    std::vector<ast::IdentifierVariant>* params, ast::Statement* body,
    std::shared_ptr<Environment> closure)
    : params_(params), body_(body), closure_(std::move(closure)) {}

auto UserDefinedFunction::call(std::vector<Value> args) -> Value {
  auto environment{std::make_shared<Environment>(closure_)};
  for (size_t i = 0; i < params_->size(); ++i) {
    auto identifier{std::get<util::Box<ast::Identifier>>((*params_)[i])};
    environment->define(identifier->name, i < args.size() ? args[i] : Value());
  }
  return std::visit(InterpreterVisitor{environment}, *body_);
}

auto UserDefinedFunction::to_string() const -> std::string {
  return "[Function]";
}
}  // namespace ctjs
