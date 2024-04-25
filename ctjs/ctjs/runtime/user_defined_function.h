#pragma once

#include "ctjs/ast/ast.h"
#include "ctjs/runtime/function.h"

namespace ctjs {

class UserDefinedFunction : public Function {
 public:
  UserDefinedFunction(std::vector<ast::IdentifierVariant>* params,
                      ast::Statement* body,
                      std::shared_ptr<class Environment> closure);

  auto call(std::vector<Value> args) -> Value override;

  [[nodiscard]] auto to_string() const -> std::string override;

 private:
  std::vector<ast::IdentifierVariant>* params_;
  ast::Statement* body_;
  std::shared_ptr<Environment> closure_;
};

}  // namespace ctjs