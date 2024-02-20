#pragma once

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"

namespace ctjs::ast {
class WhileStatement : public Statement {
 public:
  WhileStatement(std::string file_name, SourceLocation loc,
                 std::shared_ptr<Expression> condition,
                 std::shared_ptr<Statement> body);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::shared_ptr<Expression> condition_;
  std::shared_ptr<Statement> body_;
};
}  // namespace ctjs::ast
