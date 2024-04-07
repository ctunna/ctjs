#include "ctjs/runtime/function.h"

#include <variant>

#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"
#include "ctjs/util/box.h"
#include "ctjs/visitor/interpreter_visitor.h"

namespace ctjs {
Function::Function(std::vector<ast::IdentifierVariant>* params,
                   ast::Statement* body, Environment* closure)
    : params_(params), body_(body), closure_(closure) {}

Value Function::call(std::vector<Value> args) {
  Environment environment{closure_};
  for (size_t i = 0; i < params_->size(); ++i) {
    auto id{std::get<util::Box<ast::Identifier>>((*params_)[i])};
    environment.define(id->name, i < args.size() ? args[i] : Value());
  }
  return std::visit(InterpreterVisitor{&environment}, *body_);
}

auto Function::to_string() const -> std::string { return "[Function]"; }
}  // namespace ctjs
