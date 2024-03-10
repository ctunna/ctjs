#include "ctjs/ast/object_expression.h"

namespace ctjs::ast {
Property::Property(IdentifierPtr key, ExpressionPtr value)
    : key(key), value(value) {}

ObjectExpression::ObjectExpression(std::string file_name, SourceLocation loc,
                                   std::vector<Property> properties)
    : file_name(file_name), loc(loc), properties(properties) {}

}  // namespace ctjs::ast
