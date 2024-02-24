#include "ctjs/runtime/function.h"

#include "ctjs/ast/function_declaration.h"
#include "ctjs/ast/interpreter_visitor.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"

namespace ctjs {
Function::Function(std::weak_ptr<ast::FunctionDeclaration> declaration,
                   std::weak_ptr<Environment> closure)
    : declaration_(declaration), closure_(std::move(closure)) {}

Value Function::call(std::vector<Value> args) {
  if (auto decl = declaration_.lock(); decl) {
    if (auto closure = closure_.lock(); closure) {
      auto copy{std::make_shared<Environment>(*closure)};
      auto params{decl->params};
      for (size_t i = 0; i < params.size(); ++i) {
        auto id{std::get<std::shared_ptr<ast::Identifier>>(params[i])};
        copy->set(id->name, i < args.size() ? args[i] : Value());
      }
      return std::visit(ast::InterpreterVisitor{}, decl->body,
                        EnvironmentPtr{copy});
    }
    throw std::runtime_error("Function closure has been deleted");
  }
  throw std::runtime_error("Function declaration has been deleted");
}
}  // namespace ctjs
