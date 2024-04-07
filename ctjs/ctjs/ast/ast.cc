#include "ctjs/ast/ast.h"

namespace ctjs::ast {
ArrayExpression::ArrayExpression(SourceLocation loc,
                                 std::vector<Expression> elements)
    : loc(loc), elements(std::move(elements)) {}

AssignmentExpression::AssignmentExpression(SourceLocation loc, Expression left,
                                           Expression right)
    : loc(loc), left(std::move(left)), right(std::move(right)) {}

BinaryExpression::BinaryExpression(SourceLocation loc, BinaryOperator op,
                                   Expression left, Expression right)
    : loc(loc), op(op), left(std::move(left)), right(std::move(right)) {}

BlockStatement::BlockStatement(SourceLocation loc, std::vector<Statement> body)
    : loc(loc), body(std::move(body)) {}

CallExpression::CallExpression(SourceLocation loc, Expression callee,
                               std::vector<Expression> arguments)
    : loc(loc), callee(std::move(callee)), arguments(std::move(arguments)) {}

ExpressionStatement::ExpressionStatement(SourceLocation loc,
                                         Expression expression)
    : expression_(expression), loc(loc) {}

ForInStatement::ForInStatement(SourceLocation loc, IdentifierVariant left,
                               Expression right, Statement body)
    : loc(loc), left(left), right(right), body(body) {}

FunctionDeclaration::FunctionDeclaration(SourceLocation loc,
                                         IdentifierVariant id,
                                         std::vector<IdentifierVariant> params,
                                         Statement body)
    : loc(loc),
      id(std::move(id)),
      params(std::move(params)),
      body(std::move(body)) {}

FunctionExpression::FunctionExpression(SourceLocation loc,
                                       std::vector<IdentifierVariant> params,
                                       Statement body)
    : loc(loc), params(std::move(params)), body(std::move(body)) {}

Identifier::Identifier(SourceLocation loc, std::string name)
    : loc(loc), name(name) {}

Literal::Literal(SourceLocation loc, Value value)
    : loc(loc), value(std::move(value)) {}

MemberExpression::MemberExpression(SourceLocation loc, Expression object,
                                   Expression property)
    : loc(loc), object(std::move(object)), property(std::move(property)) {}

Property::Property(IdentifierVariant key, Expression value)
    : key(key), value(value) {}

ObjectExpression::ObjectExpression(SourceLocation loc,
                                   std::vector<Property> properties)
    : loc(loc), properties(properties) {}

Program::Program(SourceLocation loc, std::vector<Statement> body)
    : loc(loc), body(body) {}

ReturnStatement::ReturnStatement(SourceLocation loc,
                                 std::optional<Expression> argument)
    : loc(loc), argument_(argument) {}

VariableDeclaration::VariableDeclaration(
    SourceLocation loc, std::vector<VariableDeclaratorVariant> declarations)
    : loc(loc), declarations(declarations) {}

VariableDeclarator::VariableDeclarator(SourceLocation loc, IdentifierVariant id,
                                       Expression init)
    : loc(loc), id(id), init(init) {}

WhileStatement::WhileStatement(SourceLocation loc, Expression condition,
                               Statement body)
    : loc(loc), condition(condition), body(body) {}

IfStatement::IfStatement(SourceLocation loc, Expression test,
                         Statement consequent,
                         std::optional<Statement> alternate)
    : loc(loc), test(test), consquent(consequent), alternate(alternate) {}

}  // namespace ctjs::ast
