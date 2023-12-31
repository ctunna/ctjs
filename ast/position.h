#pragma once

namespace ast {
class Position {
public:
  const int line;
  const int column;
  Position(int line, int column) : line(line), column(column) {}
};
} // namespace ast

