#pragma once

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"

namespace ctjs::ast {
class ExpressionStatement : public Statement {
 public:
  ExpressionStatement(std::string file_name, SourceLocation loc,
                      std::shared_ptr<Expression> expression);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::shared_ptr<Expression> expression_;
  std::string file_name_;
  SourceLocation loc_;
};
}  // namespace ctjs::ast
