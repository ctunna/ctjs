#include "ctjs/ast/call_expression.h"

namespace ctjs::ast {
CallExpression::CallExpression(std::string file_name, SourceLocation loc,
                               ExpressionPtr callee,
                               std::vector<ExpressionPtr> arguments)
    : file_name(file_name), loc(loc), callee(callee), arguments(arguments) {}

}  // namespace ctjs::ast
