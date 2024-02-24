#include "ctjs/ast/while_statement.h"

namespace ctjs::ast {
WhileStatement::WhileStatement(std::string file_name, SourceLocation loc,
                               ExpressionPtr condition, StatementPtr body)
    : file_name(file_name), loc(loc), condition(condition), body(body) {}

}  // namespace ctjs::ast
