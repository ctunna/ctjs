#include "ctjs/ast/position.h"

namespace ctjs::ast {
Position::Position(size_t line, size_t column) : line_(line), column_(column) {}
}  // namespace ctjs::ast
