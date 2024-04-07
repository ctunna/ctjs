#pragma once

#include <cstddef>

namespace ctjs::ast {
class Position {
 public:
  Position(size_t line, size_t column);

 private:
  size_t line_;
  size_t column_;
};
}  // namespace ctjs::ast
