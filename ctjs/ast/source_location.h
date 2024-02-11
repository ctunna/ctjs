#pragma once

#include <string>

#include "position.h"

namespace ctjs::ast {
class SourceLocation {
 public:
  SourceLocation(std::string source, Position start, Position end);

 private:
  std::string source;
  Position start;
  Position end;
};
}  // namespace ctjs::ast
