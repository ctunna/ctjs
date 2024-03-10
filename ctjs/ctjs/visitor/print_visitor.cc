#include "ctjs/visitor/print_visitor.h"

#include <iostream>
#include <string>
#include <variant>

namespace ctjs {

void PrintVisitor::operator()(std::shared_ptr<ast::Program> program) const {
  std::cout << std::string(indent_, ' ') << "Program([\n";
  for (auto& statement : program->body) {
    std::visit(PrintVisitor{indent_ + 2}, statement);
    std::cout << "\n";
  }
  std::cout << "])";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::BlockStatement> statement) const {
  std::cout << std::string(indent_, ' ') << "BlockStatement([\n";
  for (auto& statement : statement->body) {
    std::visit(PrintVisitor{indent_ + 2}, statement);
    std::cout << "\n";
  }
  std::cout << std::string(indent_, ' ') << "])";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::ReturnStatement> statement) const {
  std::cout << std::string(indent_, ' ') << "ReturnStatement(\n";
  if (statement->argument_) {
    std::visit(PrintVisitor{indent_ + 2}, *statement->argument_);
  } else {
    std::cout << std::string(indent_ + 2, ' ') << "null\n";
  }
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::VariableDeclaration> decl) const {
  std::cout << std::string(indent_, ' ') << "VariableDeclaration([";
  for (auto& d : decl->declarations) {
    std::cout << "\n";
    std::visit(PrintVisitor{indent_ + 2}, d);
    std::cout << "\n";
  }
  std::cout << std::string(indent_, ' ') << "])";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::VariableDeclarator> decl) const {
  std::cout << std::string(indent_, ' ') << "VariableDeclarator(";
  std::cout << "\n";
  std::visit(PrintVisitor{indent_ + 2}, decl->id);
  std::cout << ", ";
  std::cout << "\n";
  std::visit(PrintVisitor{indent_ + 2}, decl->init);
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::IfStatement> statement) const {
  std::cout << std::string(indent_, ' ') << "IfStatement(\n";
  std::visit(PrintVisitor{indent_ + 2}, statement->test);
  std::cout << "\n";
  std::visit(PrintVisitor{indent_ + 2}, statement->consquent);
  std::cout << "\n";
  if (statement->alternate) {
    std::visit(PrintVisitor{indent_ + 2}, *statement->alternate);
  } else {
    std::cout << std::string(indent_ + 2, ' ') << "null";
  }
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::WhileStatement> statement) const {
  std::cout << std::string(indent_, ' ') << "WhileStatement(\n";
  std::visit(PrintVisitor{indent_ + 2}, statement->condition);
  std::cout << ",\n";
  std::visit(PrintVisitor{indent_ + 2}, statement->body);
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::ForInStatement> statement) const {
  std::cout << std::string(indent_, ' ') << "ForInStatement(\n";
  std::visit(PrintVisitor{indent_ + 2}, statement->left);
  std::cout << ",\n";
  std::visit(PrintVisitor{indent_ + 2}, statement->right);
  std::cout << ",\n";
  std::visit(PrintVisitor{indent_ + 2}, statement->body);
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::FunctionDeclaration> decl) const {
  std::cout << std::string(indent_, ' ') << "FunctionDeclaration(\n";
  std::visit(PrintVisitor{indent_ + 2}, decl->id);
  std::cout << "\n";
  for (auto const& param : decl->params) {
    std::visit(PrintVisitor{indent_ + 2}, param);
    std::cout << "\n";
  }
  std::visit(PrintVisitor{indent_ + 2}, decl->body);
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::ExpressionStatement> statement) const {
  std::cout << std::string(indent_, ' ') << "ExpressionStatement(\n";
  std::visit(PrintVisitor{indent_ + 2}, statement->expression_);
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}
void PrintVisitor::operator()(
    std::shared_ptr<ast::ArrayExpression> expression) const {
  std::cout << std::string(indent_, ' ') << "ArrayExpression(";
  std::cout << "\n";
  for (auto const& element : expression->elements) {
    std::visit(PrintVisitor{indent_ + 2}, element);
    std::cout << "\n";
  }
  std::cout << std::string(indent_, ' ') << ")";
}
void PrintVisitor::operator()(
    std::shared_ptr<ast::AssignmentExpression> expression) const {
  std::cout << std::string(indent_, ' ') << "AssignmentExpression(";
  std::cout << "\n";
  std::visit(PrintVisitor{indent_ + 2}, expression->left);
  std::cout << ", ";
  std::cout << "\n";
  std::visit(PrintVisitor{indent_ + 2}, expression->right);
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::BinaryExpression> expression) const {
  std::cout << std::string(indent_, ' ') << "BinaryExpression("
            << to_symbol(expression->op) << ",\n";
  std::visit(PrintVisitor{indent_ + 2}, expression->left);
  std::cout << ",\n";
  std::visit(PrintVisitor{indent_ + 2}, expression->right);
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::CallExpression> expression) const {
  std::cout << std::string(indent_, ' ') << "CallExpression(\n";
  std::visit(PrintVisitor{indent_ + 2}, expression->callee);
  std::cout << ",\n";
  for (auto& arg : expression->arguments) {
    std::visit(PrintVisitor{indent_ + 2}, arg);
    std::cout << ",\n";
  }
  std::cout << std::string(indent_, ' ') << ")";
}
void PrintVisitor::operator()(std::shared_ptr<ast::Identifier> id) const {
  std::cout << std::string(indent_, ' ') << "Identifier(" << id->name << ")";
}

void PrintVisitor::operator()(std::shared_ptr<ast::Literal> literal) const {
  std::cout << std::string(indent_, ' ') << "Literal("
            << literal->value.to_string() << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::MemberExpression> expression) const {
  std::cout << std::string(indent_, ' ') << "MemberExpression(\n";
  std::visit(PrintVisitor{indent_ + 2}, expression->object);
  std::cout << ",\n";
  std::visit(PrintVisitor{indent_ + 2}, expression->property);
  std::cout << "\n" << std::string(indent_, ' ') << ")";
}

void PrintVisitor::operator()(
    std::shared_ptr<ast::ObjectExpression> expression) const {
  std::cout << std::string(indent_, ' ') << "ObjectExpression([\n";
  for (auto& prop : expression->properties) {
    std::visit(PrintVisitor{indent_ + 2}, prop.key);
    std::cout << ": ";
    std::visit(PrintVisitor{0}, prop.value);
    std::cout << "\n";
  }
  std::cout << std::string(indent_, ' ') << "])";
}
}  // namespace ctjs
