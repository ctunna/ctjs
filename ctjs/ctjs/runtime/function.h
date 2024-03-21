#pragma once

#include <memory>
#include <vector>

#include "ctjs/ast/function_declaration.h"
#include "ctjs/runtime/object.h"

namespace ctjs {
class Value;

class Environment;

class Function : public Object {
 public:
  Function(std::weak_ptr<ast::FunctionDeclaration> declaration,
           std::weak_ptr<Environment> closure);

  Value call(std::vector<Value> args);

  auto to_string() const -> std::string override;

 private:
  std::weak_ptr<ast::FunctionDeclaration> declaration_;
  std::weak_ptr<Environment> closure_;
};

}  // namespace ctjs
