#pragma once

#include <string>
#include <vector>

#include "declaration.h"
#include "variable_declarator.h"

namespace ctjs::ast {
class VariableDeclaration : public Declaration {
 public:
  VariableDeclaration(
      std::string file_name, SourceLocation loc,
      std::vector<std::shared_ptr<VariableDeclarator>> declarations);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::string const kind_{"var"};
  std::vector<std::shared_ptr<VariableDeclarator>> declarations_;
};
}  // namespace ctjs::ast
