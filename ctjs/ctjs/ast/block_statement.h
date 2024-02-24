#pragma once

#include <memory>
#include <vector>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"

namespace ctjs::ast {
class BlockStatement {
 public:
  BlockStatement(std::string file_name, SourceLocation loc,
                 std::vector<StatementPtr> body);

  std::string const file_name;
  SourceLocation const loc;
  std::vector<StatementPtr> const body;
};
}  // namespace ctjs::ast
