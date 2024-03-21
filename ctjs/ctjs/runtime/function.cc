#include "ctjs/runtime/function.h"

#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"
#include "ctjs/visitor/interpreter_visitor.h"

namespace ctjs {
Function::Function(std::weak_ptr<ast::FunctionDeclaration> declaration,
                   std::weak_ptr<Environment> closure)
    : declaration_(declaration), closure_(std::move(closure)) {}

Value Function::call(std::vector<Value> args) {
  if (auto decl = declaration_.lock(); decl) {
    if (auto closure = closure_.lock(); closure) {
      auto environment{std::make_shared<Environment>(closure)};
      auto params{decl->params};
      for (size_t i = 0; i < params.size(); ++i) {
        auto id{std::get<std::shared_ptr<ast::Identifier>>(params[i])};
        environment->define(id->name, i < args.size() ? args[i] : Value());
      }
      return std::visit(InterpreterVisitor{}, decl->body,
                        EnvironmentPtr{environment});
    }
    throw std::runtime_error("Function closure has been deleted");
  }
  throw std::runtime_error("Function declaration has been deleted");
}

auto Function::to_string() const -> std::string { return "[Function]"; }
}  // namespace ctjs
