#include "ctjs/ast/function_declaration.h"

#include <iostream>

#include "ctjs/runtime/function.h"

namespace ctjs::ast {
FunctionDeclaration::FunctionDeclaration(std::string file_name,
                                         SourceLocation loc, IdentifierPtr id,
                                         std::vector<IdentifierPtr> params,
                                         StatementPtr body)
    : file_name(file_name), loc(loc), id(id), params(params), body(body) {}


}  // namespace ctjs::ast
