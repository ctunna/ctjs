#include "ctjs/ast/program.h"

#include <iostream>

namespace ctjs::ast {
Program::Program(std::string file_name, SourceLocation loc,
                 std::vector<StatementPtr> body)
    : file_name(file_name), loc(loc), body(body) {}

}  // namespace ctjs::ast
