#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"

namespace ctjs::ast {
class CallExpression : public Expression {
 public:
  CallExpression(std::string file_name, SourceLocation loc,
                 std::shared_ptr<Expression> callee,
                 std::vector<std::shared_ptr<Expression>> arguments);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::shared_ptr<Expression> callee_;
  std::vector<std::shared_ptr<Expression>> arguments_;
};
}  // namespace ctjs::ast
