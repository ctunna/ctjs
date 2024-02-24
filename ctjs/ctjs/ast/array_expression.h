#pragma once

#include <memory>
#include <string>
#include <vector>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"

namespace ctjs::ast {
class ArrayExpression {
 public:
  ArrayExpression(std::string file_name, SourceLocation loc,
                  std::vector<ExpressionPtr> elements);

  std::string const file_name;
  SourceLocation const loc;
  std::vector<ExpressionPtr> const elements;
};
}  // namespace ctjs::ast
