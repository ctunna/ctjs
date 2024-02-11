#pragma once

namespace ctjs::ast {
class Position {
 public:
  Position(int line, int column);

 private:
  [[maybe_unused]] int line_;
  [[maybe_unused]] int column_;
};
}  // namespace ctjs::ast
