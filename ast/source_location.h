#pragma once

#include <string>
#include "position.h"

namespace ast {
class SourceLocation {
public:
  const std::string source;
  const Position start;
  const Position end;
};
} // namespace ast

