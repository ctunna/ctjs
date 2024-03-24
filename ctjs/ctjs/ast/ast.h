#pragma once

#include <memory>
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
    util::Box<class MemberExpression>, util::Box<class ObjectExpression>>;

using VariableDeclaratorVariant =
    std::variant<util::Box<class VariableDeclarator>>;

using IdentifierVariant = std::variant<util::Box<class Identifier>>;

class ArrayExpression {
 public:
  ArrayExpression(std::string file_name, SourceLocation loc,
                  std::vector<Expression> elements);

  std::string file_name;
  SourceLocation loc;
  std::vector<Expression> elements;
};

class AssignmentExpression {
 public:
  AssignmentExpression(std::string file_name, SourceLocation loc,
                       Expression left, Expression right);

  std::string file_name;
  SourceLocation loc;
  Expression left;
  Expression right;
};

class BinaryExpression {
 public:
  BinaryExpression(std::string file_name, SourceLocation loc, BinaryOperator op,
                   Expression left, Expression right);

  std::string file_name;
  SourceLocation loc;
  BinaryOperator op;
  Expression left;
  Expression right;
};

class BlockStatement {
 public:
  BlockStatement(std::string file_name, SourceLocation loc,
                 std::vector<Statement> body);

  std::string file_name;
  SourceLocation loc;
  std::vector<Statement> body;
};

class CallExpression {
 public:
  CallExpression(std::string file_name, SourceLocation loc, Expression callee,
                 std::vector<Expression> arguments);

  std::string file_name;
  SourceLocation loc;
  Expression callee;
  std::vector<Expression> arguments;
};

class ExpressionStatement {
 public:
  ExpressionStatement(std::string file_name, SourceLocation loc,
                      Expression expression);

  Expression expression_;
  std::string file_name;
  SourceLocation loc;
};

class ForInStatement {
 public:
  ForInStatement(std::string file_name, SourceLocation loc,
                 IdentifierVariant left, Expression right, Statement body);

  std::string file_name;
  SourceLocation loc;
  IdentifierVariant left;
  Expression right;
  Statement body;
};

class FunctionDeclaration {
 public:
  FunctionDeclaration(std::string file_name, SourceLocation loc,
                      IdentifierVariant id,
                      std::vector<IdentifierVariant> params, Statement body);

  std::string file_name;
  SourceLocation loc;
  IdentifierVariant id;
  std::vector<IdentifierVariant> params;
  Statement body;
};

class Identifier {
 public:
  Identifier(std::string file_name, SourceLocation loc, std::string name);

  std::string file_name;
  SourceLocation loc;
  std::string name;
};

class Literal {
 public:
  Literal(std::string file_name, SourceLocation loc, Value value);

  std::string file_name;
  SourceLocation loc;
  Value value;
};

class MemberExpression {
 public:
  MemberExpression(std::string file_name, SourceLocation loc, Expression object,
                   Expression literal);

  std::string file_name;
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
  ObjectExpression(std::string file_name, SourceLocation loc,
                   std::vector<Property> properties);

  std::string file_name;
  SourceLocation loc;
  std::vector<Property> properties;
};

class Program {
 public:
  Program(std::string file_name, SourceLocation loc,
          std::vector<Statement> body);

  std::string file_name;
  SourceLocation loc;
  std::vector<Statement> body;
};

class ReturnStatement {
 public:
  ReturnStatement(std::string file_name, SourceLocation loc,
                  std::optional<Expression> argument);

  std::string file_name;
  SourceLocation loc;
  std::optional<Expression> argument_;
};

class VariableDeclaration {
 public:
  VariableDeclaration(std::string file_name, SourceLocation loc,
                      std::vector<VariableDeclaratorVariant> declarations);

  std::string file_name;
  SourceLocation loc;
  std::string kind{"var"};
  std::vector<VariableDeclaratorVariant> declarations;
};

class VariableDeclarator {
 public:
  VariableDeclarator(std::string file_name, SourceLocation loc,
                     IdentifierVariant id, Expression init);

  std::string file_name;
  SourceLocation loc;
  IdentifierVariant id;
  Expression init;
};

class WhileStatement {
 public:
  WhileStatement(std::string file_name, SourceLocation loc,
                 Expression condition, Statement body);

  std::string file_name;
  SourceLocation loc;
  Expression condition;
  Statement body;
};

class IfStatement {
 public:
  IfStatement(std::string file_name, SourceLocation loc, Expression test,
              Statement consequent, std::optional<Statement> alternate);

  std::string file_name;
  SourceLocation loc;
  Expression test;
  Statement consquent;
  std::optional<Statement> alternate;
};

}  // namespace ctjs::ast