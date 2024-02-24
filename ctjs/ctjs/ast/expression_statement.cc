#include "ctjs/ast/expression_statement.h"

#include <iostream>

namespace ctjs::ast {
ExpressionStatement::ExpressionStatement(std::string file_name,
                                         SourceLocation loc,
                                         ExpressionPtr expression)
    : expression_(expression), file_name(file_name), loc(loc) {}



}  // namespace ctjs::ast
