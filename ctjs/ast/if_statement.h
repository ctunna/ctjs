#pragma once

#include "expression.h"
#include "source_location.h"
#include "statement.h"

namespace ctjs::ast {
class IfStatement : public Statement {
 public:
  IfStatement(std::string file_name, SourceLocation loc,
              std::shared_ptr<Expression> test,
              std::shared_ptr<Statement> consequent,
              std::shared_ptr<Statement> alternate);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::shared_ptr<Expression> test_;
  std::shared_ptr<Statement> consequent_;
  std::shared_ptr<Statement> alternate_;
};
}  // namespace ctjs::ast
