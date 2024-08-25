#include "ctjs/interpreter.h"

#include "ctjs/parser.h"
#include "ctjs/runtime/builtin.h"
#include "ctjs/util/file/read_all_text.h"
#include "ctjs/visitor/interpreter_visitor.h"

namespace ctjs {
Interpreter::Interpreter() { Builtin::apply(environment_); }

void Interpreter::eval(std::string file_name, std::string_view code) {
  Parser parser{std::move(file_name), code};
  InterpreterVisitor visitor{environment_};
  runspace_.emplace_back(parser.parse());
  std::visit(visitor, runspace_.back());
}

void Interpreter::eval(std::string_view code) { return eval("REPL", code); }

void Interpreter::eval_file(const std::string& file_name) {
  auto code{util::file::read_all_text(file_name)};
  eval(file_name, code);
}
}  // namespace ctjs
