#pragma once

#include <memory>
#include <vector>

namespace ctjs {
namespace ast {
class FunctionDeclaration;
}

class Value;

class Environment;

class Function {
 public:
  Function() = default;

  Function(std::weak_ptr<ast::FunctionDeclaration> declaration,
           std::weak_ptr<Environment> closure);

  Value call(std::vector<Value> args);

 private:
  std::weak_ptr<ast::FunctionDeclaration> declaration_;
  std::weak_ptr<Environment> closure_;
};

}  // namespace ctjs
