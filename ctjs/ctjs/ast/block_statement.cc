#include "ctjs/ast/block_statement.h"

namespace ctjs::ast {
BlockStatement::BlockStatement(std::string file_name, SourceLocation loc,
                               std::vector<StatementPtr> body)
    : file_name(file_name), loc(loc), body(body) {}


}  // namespace ctjs::ast
