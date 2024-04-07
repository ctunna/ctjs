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
  static void eval(Environment& environment, std::string_view code) {
    Parser p{code};
    InterpreterVisitor visitor{&environment};
    ctjs::ast::AstNode program{p.parse()};
    std::visit(visitor, program);
  }
};
}  // namespace ctjs
