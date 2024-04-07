#pragma once

#include <string_view>
#include <variant>

#include "ctjs/ast/ast.h"
#include "ctjs/parser.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/tokenizer.h"
#include "ctjs/util/file/read_all_text.h"
#include "ctjs/visitor/interpreter_visitor.h"

namespace ctjs {
class Interpreter {
 public:
  static void eval(Environment& environment, std::string file_name,
                   std::string_view code) {
    Parser parser{file_name, code};
    InterpreterVisitor visitor{&environment};
    ctjs::ast::AstNode program{parser.parse()};
    std::visit(visitor, program);
  }

  static void eval(Environment& environment, std::string_view code) {
    return eval(environment, "REPL", code);
  }

  static void eval_file(Environment& environment, std::string file_name) {
    eval(environment, file_name, util::file::read_all_text(file_name));
  }
};
}  // namespace ctjs
