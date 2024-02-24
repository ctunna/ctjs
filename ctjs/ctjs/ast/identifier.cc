#include "ctjs/ast/identifier.h"

#include <iostream>

namespace ctjs::ast {
Identifier::Identifier(std::string file_name, SourceLocation loc,
                       std::string name)
    : file_name(file_name), loc(loc), name(name) {}

}  // namespace ctjs::ast
