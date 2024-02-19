#pragma once

#include <string>

#include "expression.h"
#include "identifier.h"

namespace ctjs::ast {
class VariableDeclarator : public Node {
 public:
  VariableDeclarator(std::string file_name, SourceLocation loc,
                     std::shared_ptr<Identifier> id,
                     std::shared_ptr<Expression> init);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::shared_ptr<Identifier> id_;
  std::shared_ptr<Expression> init_;
};
}  // namespace ctjs::ast
