#pragma once

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "ctjs/ast/binary_operator.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/runtime/value.h"
#include "ctjs/util/box.h"

namespace ctjs::ast {

using AstNode = std::variant<
    util::Box<class Program>, util::Box<class ArrayExpression>,
    util::Box<class AssignmentExpression>, util::Box<class BinaryExpression>,
    util::Box<class BlockStatement>, util::Box<class CallExpression>,
    util::Box<class ExpressionStatement>, util::Box<class FunctionDeclaration>,
    util::Box<class Identifier>, util::Box<class IfStatement>,
    util::Box<class Literal>, util::Box<class ReturnStatement>,
    util::Box<class VariableDeclaration>, util::Box<class WhileStatement>>;

using Statement = std::variant<
    util::Box<class BlockStatement>, util::Box<class ExpressionStatement>,
    util::Box<class IfStatement>, util::Box<class ReturnStatement>,
    util::Box<class VariableDeclaration>, util::Box<class FunctionDeclaration>,
    util::Box<class WhileStatement>, util::Box<class ForInStatement>>;

using Expression = std::variant<
    util::Box<class ArrayExpression>, util::Box<class AssignmentExpression>,
    util::Box<class BinaryExpression>, util::Box<class CallExpression>,
    util::Box<class Identifier>, util::Box<class Literal>,
    util::Box<class MemberExpression>, util::Box<class ObjectExpression>,
    util::Box<class FunctionExpression>>;

using VariableDeclaratorVariant =
    std::variant<util::Box<class VariableDeclarator>>;

using IdentifierVariant = std::variant<util::Box<class Identifier>>;

class ArrayExpression {
 public:
  ArrayExpression(SourceLocation loc, std::vector<Expression> elements);

  SourceLocation loc;
  std::vector<Expression> elements;
};

class AssignmentExpression {
 public:
  AssignmentExpression(SourceLocation loc, Expression left, Expression right);

  SourceLocation loc;
  Expression left;
  Expression right;
};

class BinaryExpression {
 public:
  BinaryExpression(SourceLocation loc, BinaryOperator op, Expression left,
                   Expression right);

  SourceLocation loc;
  BinaryOperator op;
  Expression left;
  Expression right;
};

class BlockStatement {
 public:
  BlockStatement(SourceLocation loc, std::vector<Statement> body);

  SourceLocation loc;
  std::vector<Statement> body;
};

class CallExpression {
 public:
  CallExpression(SourceLocation loc, Expression callee,
                 std::vector<Expression> arguments);

  SourceLocation loc;
  Expression callee;
  std::vector<Expression> arguments;
};

class ExpressionStatement {
 public:
  ExpressionStatement(SourceLocation loc, Expression expression);

  Expression expression_;

  SourceLocation loc;
};

class ForInStatement {
 public:
  ForInStatement(SourceLocation loc, IdentifierVariant left, Expression right,
                 Statement body);

  SourceLocation loc;
  IdentifierVariant left;
  Expression right;
  Statement body;
};

class FunctionDeclaration {
 public:
  FunctionDeclaration(SourceLocation loc, IdentifierVariant id,
                      std::vector<IdentifierVariant> params, Statement body);

  SourceLocation loc;
  IdentifierVariant id;
  std::vector<IdentifierVariant> params;
  Statement body;
};

class FunctionExpression {
 public:
  FunctionExpression(SourceLocation loc, std::vector<IdentifierVariant> params,
                     Statement body);
  SourceLocation loc;
  std::vector<IdentifierVariant> params;
  Statement body;
};

class Identifier {
 public:
  Identifier(SourceLocation loc, std::string name);

  SourceLocation loc;
  std::string name;
};

class Literal {
 public:
  Literal(SourceLocation loc, Value value);

  SourceLocation loc;
  Value value;
};

class MemberExpression {
 public:
  MemberExpression(SourceLocation loc, Expression object, Expression literal);

  SourceLocation loc;
  Expression object;
  Expression property;
};

class Property {
 public:
  Property(IdentifierVariant key, Expression value);

  IdentifierVariant key;
  Expression value;
};

class ObjectExpression {
 public:
  ObjectExpression(SourceLocation loc, std::vector<Property> properties);

  SourceLocation loc;
  std::vector<Property> properties;
};

class Program {
 public:
  Program(SourceLocation loc, std::vector<Statement> body);

  SourceLocation loc;
  std::vector<Statement> body;
};

class ReturnStatement {
 public:
  ReturnStatement(SourceLocation loc, std::optional<Expression> argument);

  SourceLocation loc;
  std::optional<Expression> argument_;
};

class VariableDeclaration {
 public:
  VariableDeclaration(SourceLocation loc,
                      std::vector<VariableDeclaratorVariant> declarations);

  SourceLocation loc;
  std::string kind{"var"};
  std::vector<VariableDeclaratorVariant> declarations;
};

class VariableDeclarator {
 public:
  VariableDeclarator(SourceLocation loc, IdentifierVariant id, Expression init);

  SourceLocation loc;
  IdentifierVariant id;
  Expression init;
};

class WhileStatement {
 public:
  WhileStatement(SourceLocation loc, Expression condition, Statement body);

  SourceLocation loc;
  Expression condition;
  Statement body;
};

class IfStatement {
 public:
  IfStatement(SourceLocation loc, Expression test, Statement consequent,
              std::optional<Statement> alternate);

  SourceLocation loc;
  Expression test;
  Statement consquent;
  std::optional<Statement> alternate;
};

}  // namespace ctjs::ast