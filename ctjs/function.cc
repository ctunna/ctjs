#include "function.h"

#include "ast/function_declaration.h"
#include "environment.h"
#include "value.h"

namespace ctjs {
Function::Function(std::weak_ptr<ast::FunctionDeclaration> declaration,
                   std::weak_ptr<Environment> closure)
    : declaration_(declaration), closure_(std::move(closure)) {}

Value Function::call([[maybe_unused]] std::vector<Value> args) {
  if (auto decl = declaration_.lock(); decl) {
    if (auto closure = closure_.lock(); closure) {
      auto copy{std::make_shared<Environment>(*closure)};
      auto params{decl->params()};
      for (size_t i = 0; i < params.size(); ++i) {
        copy->set(params[i]->name(), i < args.size() ? args[i] : Value());
      }
      return decl->body()->evaluate(copy);
    }
    throw std::runtime_error("Function closure has been deleted");
  }
  throw std::runtime_error("Function declaration has been deleted");
}
}  // namespace ctjs
