#pragma once

#include <string>

#include "source_location.h"

namespace ast {
class Node {
public:
  const std::string name;
  const SourceLocation loc;

  Node(std::string name, SourceLocation loc) : name(name), loc(loc) {}
};
} // namespace ast

