#pragma once

#include <memory>
#include <vector>

#include "ctjs/ast/ast.h"
#include "ctjs/runtime/object.h"
#include "ctjs/util/box.h"

namespace ctjs {
class Value;

class Environment;

class Function : public Object {
 public:
  Function(ast::FunctionDeclaration* declaration, Environment* closure);

  Value call(std::vector<Value> args);

  auto to_string() const -> std::string override;

 private:
  ast::FunctionDeclaration* declaration_;
  Environment* closure_;
};

}  // namespace ctjs
