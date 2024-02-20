#include "ctjs/ast/position.h"

namespace ctjs::ast {
Position::Position(int line, int column) : line_(line), column_(column) {}
}  // namespace ctjs::ast
