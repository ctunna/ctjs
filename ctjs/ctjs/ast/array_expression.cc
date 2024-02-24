#include "ctjs/ast/array_expression.h"

#include <iostream>

namespace ctjs::ast {
ArrayExpression::ArrayExpression(std::string file_name, SourceLocation loc,
                                 std::vector<ExpressionPtr> elements)
    : file_name(file_name), loc(loc), elements(elements) {}



}  // namespace ctjs::ast