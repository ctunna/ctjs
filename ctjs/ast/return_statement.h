#pragma once

#include <memory>

#include "expression.h"
#include "source_location.h"
#include "statement.h"

namespace ctjs::ast {

class ReturnStatement : public Statement {
 public:
  ReturnStatement(std::string file_name, SourceLocation loc,
                  std::shared_ptr<Expression> argument);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::shared_ptr<Expression> argument_;
};

}  // namespace ctjs::ast
