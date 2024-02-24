#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <variant>

#include "ctjs/ast/ast_node.h"
#include "ctjs/parser.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/tokenizer.h"
#include "ctjs/visitor/interpreter_visitor.h"
#include "ctjs/visitor/print_visitor.h"

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }
  std::ifstream file(argv[1]);
  std::string code((std::istreambuf_iterator<char>(file)),
                   std::istreambuf_iterator<char>());
  ctjs::Parser p{code};
  ctjs::ast::AstNode program{p.parse()};
  std::visit(ctjs::PrintVisitor{0}, program);

  std::cout << std::endl;

  auto env{std::make_shared<ctjs::Environment>()};
  std::visit(ctjs::InterpreterVisitor{}, program, ctjs::EnvironmentPtr{env});

  env->to_string();

  return 0;
}
