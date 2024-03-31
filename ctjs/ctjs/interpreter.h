#pragma once

#include <string_view>
#include <variant>

#include "ctjs/ast/ast.h"
#include "ctjs/parser.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/tokenizer.h"
#include "ctjs/visitor/interpreter_visitor.h"

namespace ctjs {
class Interpreter {
 public:
  void run(std::string_view code) {
    Parser p{code};
    ctjs::ast::AstNode program{p.parse()};
    std::visit(interpreter_, program);
    interpreter_.print_environment();
  }

 private:
  InterpreterVisitor interpreter_;
};
}  // namespace ctjs
