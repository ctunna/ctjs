#include "ctjs/ast/binary_expression.h"

namespace ctjs::ast {

BinaryExpression::BinaryExpression(std::string file_name, SourceLocation loc,
                                   BinaryOperator op, ExpressionPtr left,
                                   ExpressionPtr right)
    : file_name(file_name), loc(loc), op(op), left(left), right(right) {}

}  // namespace ctjs::ast
