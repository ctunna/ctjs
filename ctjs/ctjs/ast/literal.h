#pragma once

#include <string>

#include "ctjs/ast/source_location.h"
#include "ctjs/runtime/value.h"

namespace ctjs::ast {
class Literal {
 public:
  Literal(std::string file_name, SourceLocation loc, Value value);

  std::string const file_name;
  SourceLocation const loc;
  Value const value;
};
}  // namespace ctjs::ast
