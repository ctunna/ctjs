#include "ctjs/ast/ast.h"

namespace ctjs::ast {
ArrayExpression::ArrayExpression(std::string file_name, SourceLocation loc,
                                 std::vector<Expression> elements)
    : file_name(file_name), loc(loc), elements(std::move(elements)) {}

AssignmentExpression::AssignmentExpression(std::string file_name,
                                           SourceLocation loc,
                                           Expression left,
                                           Expression right)
    : file_name(file_name),
      loc(loc),
      left(std::move(left)),
      right(std::move(right)) {}

BinaryExpression::BinaryExpression(std::string file_name, SourceLocation loc,
                                   BinaryOperator op, Expression left,
                                   Expression right)
    : file_name(file_name),
      loc(loc),
      op(op),
      left(std::move(left)),
      right(std::move(right)) {}

BlockStatement::BlockStatement(std::string file_name, SourceLocation loc,
                               std::vector<Statement> body)
    : file_name(file_name), loc(loc), body(std::move(body)) {}

CallExpression::CallExpression(std::string file_name, SourceLocation loc,
                               Expression callee,
                               std::vector<Expression> arguments)
    : file_name(file_name),
      loc(loc),
      callee(std::move(callee)),
      arguments(std::move(arguments)) {}

ExpressionStatement::ExpressionStatement(std::string file_name,
                                         SourceLocation loc,
                                         Expression expression)
    : expression_(expression), file_name(file_name), loc(loc) {}

ForInStatement::ForInStatement(std::string file_name, SourceLocation loc,
                               IdentifierVariant left, Expression right,
                               Statement body)
    : file_name(file_name), loc(loc), left(left), right(right), body(body) {}

FunctionDeclaration::FunctionDeclaration(std::string file_name,
                                         SourceLocation loc, IdentifierVariant id,
                                         std::vector<IdentifierVariant> params,
                                         Statement body)
    : file_name(file_name),
      loc(loc),
      id(std::move(id)),
      params(std::move(params)),
      body(std::move(body)) {}

Identifier::Identifier(std::string file_name, SourceLocation loc,
                       std::string name)
    : file_name(file_name), loc(loc), name(name) {}

Literal::Literal(std::string file_name, SourceLocation loc, Value value)
    : file_name(file_name), loc(loc), value(std::move(value)) {}

MemberExpression::MemberExpression(std::string file_name, SourceLocation loc,
                                   Expression object, Expression property)
    : file_name(file_name),
      loc(loc),
      object(std::move(object)),
      property(std::move(property)) {}

Property::Property(IdentifierVariant key, Expression value)
    : key(key), value(value) {}

ObjectExpression::ObjectExpression(std::string file_name, SourceLocation loc,
                                   std::vector<Property> properties)
    : file_name(file_name), loc(loc), properties(properties) {}

Program::Program(std::string file_name, SourceLocation loc,
                 std::vector<Statement> body)
    : file_name(file_name), loc(loc), body(body) {}

ReturnStatement::ReturnStatement(std::string file_name, SourceLocation loc,
                                 std::optional<Expression> argument)
    : file_name(file_name), loc(loc), argument_(argument) {}

VariableDeclaration::VariableDeclaration(
    std::string file_name, SourceLocation loc,
    std::vector<VariableDeclaratorVariant> declarations)
    : file_name(file_name), loc(loc), declarations(declarations) {}

VariableDeclarator::VariableDeclarator(std::string file_name,
                                       SourceLocation loc, IdentifierVariant id,
                                       Expression init)
    : file_name(file_name), loc(loc), id(id), init(init) {}

WhileStatement::WhileStatement(std::string file_name, SourceLocation loc,
                               Expression condition, Statement body)
    : file_name(file_name), loc(loc), condition(condition), body(body) {}

IfStatement::IfStatement(std::string file_name, SourceLocation loc,
                         Expression test, Statement consequent,
                         std::optional<Statement> alternate)
    : file_name(file_name),
      loc(loc),
      test(test),
      consquent(consequent),
      alternate(alternate) {}

}  // namespace ctjs::ast
