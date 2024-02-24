#include "ctjs/ast/literal.h"

#include <iostream>

namespace ctjs::ast {
Literal::Literal(std::string file_name, SourceLocation loc, Value value)
    : file_name(file_name), loc(loc), value(value) {}

}  // namespace ctjs::ast
