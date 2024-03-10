#include "ctjs/ast/for_in_statement.h"

namespace ctjs::ast {
ForInStatement::ForInStatement(std::string file_name, SourceLocation loc,
                               IdentifierPtr left, ExpressionPtr right,
                               StatementPtr body)
    : file_name(file_name), loc(loc), left(left), right(right), body(body) {}

}  // namespace ctjs::ast
