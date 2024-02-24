#include "ctjs/ast/return_statement.h"

#include <iostream>

namespace ctjs::ast {
ReturnStatement::ReturnStatement(std::string file_name, SourceLocation loc,
                                 std::optional<ExpressionPtr> argument)
    : file_name(file_name), loc(loc), argument_(argument) {}

}  // namespace ctjs::ast