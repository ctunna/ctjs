#pragma once

#include <vector>

#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"

namespace ctjs::ast {
class Program {
 public:
  Program(std::string file_name, SourceLocation loc,
          std::vector<StatementPtr> body);

  std::string const file_name;
  SourceLocation const loc;
  std::vector<StatementPtr> const body;
};
}  // namespace ctjs::ast
