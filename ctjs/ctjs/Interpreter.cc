#include "ctjs/interpreter.h"

#include <iostream>
#include <memory>
#include <vector>

#include "ctjs/parser.h"
#include "ctjs/runtime/builtin_function.h"
#include "ctjs/util/file/read_all_text.h"
#include "ctjs/visitor/interpreter_visitor.h"

namespace ctjs {
Interpreter::Interpreter() {
  auto console{std::make_shared<Object>()};
  auto log{std::make_shared<BuiltinFunction>([](std::vector<Value> args) {
    for (auto& arg : args) {
      std::cout << arg.to_string() << ' ';
    }
    std::cout << '\n';
    return Value();
  })};
  console->set_property("log", Value(log));
  environment_->define("console", Value(console));
}

void Interpreter::eval(std::string file_name, std::string_view code) {
  Parser parser{std::move(file_name), code};
  InterpreterVisitor visitor{environment_};
  ctjs::ast::AstNode program{parser.parse()};
  std::visit(visitor, program);
}

void Interpreter::eval(std::string_view code) { return eval("REPL", code); }

void Interpreter::eval_file(const std::string& file_name) {
  eval(file_name, util::file::read_all_text(file_name));
}
}  // namespace ctjs