#include "ctjs/ast/assignment_expression.h"

namespace ctjs::ast {
AssignmentExpression::AssignmentExpression(std::string file_name,
                                           SourceLocation loc,
                                           ExpressionPtr left,
                                           ExpressionPtr right)
    : file_name(file_name), loc(loc), left(left), right(right) {}


}  // namespace ctjs::ast
