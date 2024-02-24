#pragma once

#include <memory>
#include <string>

#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/runtime/value.h"

namespace ctjs::ast {
using IdentifierPtr = std::variant<std::shared_ptr<Identifier>>;
class Identifier {
 public:
  Identifier(std::string file_name, SourceLocation loc, std::string name);

  std::string const file_name;
  SourceLocation const loc;
  std::string const name;
};
}  // namespace ctjs::ast
