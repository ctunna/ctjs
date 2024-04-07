#include "ctjs/runtime/function.h"

#include <variant>

#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"
#include "ctjs/util/box.h"
#include "ctjs/visitor/interpreter_visitor.h"

namespace ctjs {
Function::Function(ast::FunctionDeclaration* declaration, Environment* closure)
    : declaration_(declaration), closure_(std::move(closure)) {}

Value Function::call(std::vector<Value> args) {
  Environment environment{closure_};
  auto& params{declaration_->params};
  for (size_t i = 0; i < params.size(); ++i) {
    auto id{std::get<util::Box<ast::Identifier>>(params[i])};
    environment.define(id->name, i < args.size() ? args[i] : Value());
  }
  return std::visit(InterpreterVisitor{&environment}, declaration_->body);
}

auto Function::to_string() const -> std::string { return "[Function]"; }
}  // namespace ctjs
