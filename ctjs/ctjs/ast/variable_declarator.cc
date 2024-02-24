#include "ctjs/ast/variable_declarator.h"

#include <iostream>

namespace ctjs::ast {
VariableDeclarator::VariableDeclarator(std::string file_name,
                                       SourceLocation loc, IdentifierPtr id,
                                       ExpressionPtr init)
    : file_name(file_name), loc(loc), id(id), init(init) {}

}  // namespace ctjs::ast
