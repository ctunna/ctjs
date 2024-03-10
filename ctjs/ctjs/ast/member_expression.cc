#include "ctjs/ast/member_expression.h"

namespace ctjs::ast {
MemberExpression::MemberExpression(std::string file_name, SourceLocation loc,
                                   ExpressionPtr object, ExpressionPtr property)
    : file_name(file_name), loc(loc), object(object), property(property) {}

}  // namespace ctjs::ast