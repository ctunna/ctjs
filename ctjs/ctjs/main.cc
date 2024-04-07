#include <fstream>
#include <iostream>
#include <streambuf>
#include <string>
#include <variant>

#include "ctjs/ast/ast.h"
#include "ctjs/interpreter.h"
#include "ctjs/parser.h"
#include "ctjs/runtime/environment.h"
#include "ctjs/tokenizer.h"
#include "ctjs/util/file/read_all_text.h"
#include "ctjs/visitor/interpreter_visitor.h"
#include "ctjs/visitor/print_visitor.h"

using namespace ctjs;

int main(int argc, char** argv) {
  try {
    auto flag{std::string(argv[1])};
    if (flag == "-h") {
      std::cout << "Usage:\n"
                << argv[0] << " [option] <argument>\n\n"
                << "Options:\n"
                << "  -h          Show this help message\n"
                << "  <filename>  Execute the script from the provided file\n"
                << "  -p <file>   Parse the file and print the AST without "
                   "executing"
                << std::endl;
    } else if (flag == "-p") {
      if (argc < 3) {
        throw std::runtime_error{"'-p' option requires a filename argument."};
      }
      Parser parser{util::file::read_all_text(argv[2])};
      ast::AstNode program{parser.parse()};
      std::visit(PrintVisitor{0}, program);
    } else {
      Interpreter interpreter;
      Environment environment;
      interpreter.eval(environment, util::file::read_all_text(argv[1]));
      environment.print();
    }
  } catch (std::exception const& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
