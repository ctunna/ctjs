#include "ctjs/ast/ast.h"

#include <utility>

namespace ctjs::ast {
ArrayExpression::ArrayExpression(SourceLocation loc,
                                 std::vector<Expression> elements)
    : loc(std::move(loc)), elements(std::move(elements)) {}

AssignmentExpression::AssignmentExpression(SourceLocation loc, Expression left,
                                           Expression right)
    : loc(std::move(loc)), left(std::move(left)), right(std::move(right)) {}

BinaryExpression::BinaryExpression(SourceLocation loc, BinaryOperator op,
                                   Expression left, Expression right)
    : loc(std::move(loc)),
      op(op),
      left(std::move(left)),
      right(std::move(right)) {}

BlockStatement::BlockStatement(SourceLocation loc, std::vector<Statement> body)
    : loc(std::move(loc)), body(std::move(body)) {}

CallExpression::CallExpression(SourceLocation loc, Expression callee,
                               std::vector<Expression> arguments)
    : loc(std::move(loc)),
      callee(std::move(callee)),
      arguments(std::move(arguments)) {}

ExpressionStatement::ExpressionStatement(SourceLocation loc,
                                         Expression expression)
    : expression_(std::move(expression)), loc(std::move(loc)) {}

ForInStatement::ForInStatement(SourceLocation loc, IdentifierVariant left,
                               Expression right, Statement body)
    : loc(std::move(loc)),
      left(std::move(left)),
      right(std::move(right)),
      body(std::move(body)) {}

FunctionDeclaration::FunctionDeclaration(SourceLocation loc,
                                         IdentifierVariant id,
                                         std::vector<IdentifierVariant> params,
                                         Statement body)
    : loc(std::move(loc)),
      id(std::move(id)),
      params(std::move(params)),
      body(std::move(body)) {}

FunctionExpression::FunctionExpression(SourceLocation loc,
                                       std::vector<IdentifierVariant> params,
                                       Statement body)
    : loc(std::move(loc)), params(std::move(params)), body(std::move(body)) {}

Identifier::Identifier(SourceLocation loc, std::string name)
    : loc(std::move(loc)), name(std::move(name)) {}

Literal::Literal(SourceLocation loc, Value value)
    : loc(std::move(loc)), value(std::move(value)) {}

MemberExpression::MemberExpression(SourceLocation loc, Expression object,
                                   Expression property)
    : loc(std::move(loc)),
      object(std::move(object)),
      property(std::move(property)) {}

Property::Property(IdentifierVariant key, Expression value)
    : key(std::move(key)), value(std::move(value)) {}

ObjectExpression::ObjectExpression(SourceLocation loc,
                                   std::vector<Property> properties)
    : loc(std::move(loc)), properties(std::move(properties)) {}

Program::Program(SourceLocation loc, std::vector<Statement> body)
    : loc(std::move(loc)), body(std::move(body)) {}

ReturnStatement::ReturnStatement(SourceLocation loc,
                                 std::optional<Expression> argument)
    : loc(std::move(loc)), argument_(std::move(argument)) {}

VariableDeclaration::VariableDeclaration(
    SourceLocation loc, std::vector<VariableDeclaratorVariant> declarations)
    : loc(std::move(loc)), declarations(std::move(declarations)) {}

VariableDeclarator::VariableDeclarator(SourceLocation loc, IdentifierVariant id,
                                       Expression init)
    : loc(std::move(loc)), id(std::move(id)), init(std::move(init)) {}

WhileStatement::WhileStatement(SourceLocation loc, Expression condition,
                               Statement body)
    : loc(std::move(loc)),
      condition(std::move(condition)),
      body(std::move(body)) {}

IfStatement::IfStatement(SourceLocation loc, Expression test,
                         Statement consequent,
                         std::optional<Statement> alternate)
    : loc(std::move(loc)),
      test(std::move(test)),
      consquent(std::move(consequent)),
      alternate(std::move(alternate)) {}

}  // namespace ctjs::ast
