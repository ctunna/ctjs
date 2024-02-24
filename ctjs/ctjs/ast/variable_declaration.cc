#include "ctjs/ast/variable_declaration.h"

#include <iostream>

namespace ctjs::ast {
VariableDeclaration::VariableDeclaration(
    std::string file_name, SourceLocation loc,
    std::vector<VariableDeclaratorPtr> declarations)
    : file_name(file_name), loc(loc), declarations(declarations) {}

}  // namespace ctjs::ast
