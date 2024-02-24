#include "ctjs/ast/if_statement.h"

#include <iostream>

namespace ctjs::ast {
IfStatement::IfStatement(std::string file_name, SourceLocation loc,
                         ExpressionPtr test, StatementPtr consequent,
                         std::optional<StatementPtr> alternate)
    : file_name(file_name),
      loc(loc),
      test(test),
      consquent(consequent),
      alternate(alternate) {}

}  // namespace ctjs::ast
