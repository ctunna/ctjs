#pragma once

#include <memory>
#include <variant>

namespace ctjs::ast {
class ArrayExpression;
class AssignmentExpression;
class BinaryExpression;
class CallExpression;
class Identifier;
class Literal;
class MemberExpression;
class ObjectExpression;

using ExpressionPtr = std::variant<
    std::shared_ptr<ArrayExpression>, std::shared_ptr<AssignmentExpression>,
    std::shared_ptr<BinaryExpression>, std::shared_ptr<CallExpression>,
    std::shared_ptr<Identifier>, std::shared_ptr<Literal>,
    std::shared_ptr<MemberExpression>, std::shared_ptr<ObjectExpression>>;
}  // namespace ctjs::ast
