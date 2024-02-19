#pragma once

#include <memory>
#include <string>
#include <vector>

#include "expression.h"
#include "source_location.h"

namespace ctjs::ast {
class ArrayExpression : public Expression {
 public:
  ArrayExpression(std::string file_name, SourceLocation loc,
                  std::vector<std::shared_ptr<Expression>> elements);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::vector<std::shared_ptr<Expression>> elements_;
};
}  // namespace ctjs::ast