#pragma once

#include <memory>
#include <optional>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"

namespace ctjs::ast {

class ReturnStatement {
 public:
  ReturnStatement(std::string file_name, SourceLocation loc,
                  std::optional<ExpressionPtr> argument);



  std::string file_name;
  SourceLocation loc;
  std::optional<ExpressionPtr> argument_;
};

}  // namespace ctjs::ast
