#pragma once

#include <memory>
#include <string>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"

namespace ctjs::ast {
class AssignmentExpression : public Expression {
 public:
  AssignmentExpression(std::string file_name, SourceLocation loc,
                       std::shared_ptr<Expression> left,
                       std::shared_ptr<Expression> right);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::shared_ptr<Expression> left_;
  std::shared_ptr<Expression> right_;
};
}  // namespace ctjs::ast