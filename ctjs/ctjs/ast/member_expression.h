#pragma once

#include <memory>
#include <string>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"

namespace ctjs::ast {
class MemberExpression {
 public:
  MemberExpression(std::string file_name, SourceLocation loc,
                   ExpressionPtr object, ExpressionPtr literal);

  std::string const file_name;
  SourceLocation const loc;
  ExpressionPtr const object;
  ExpressionPtr const property;
};
}  // namespace ctjs::ast
