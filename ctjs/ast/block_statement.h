#pragma once

#include <memory>
#include <vector>

#include "source_location.h"
#include "statement.h"

namespace ctjs::ast {
class BlockStatement : public Statement {
 public:
  BlockStatement(std::string file_name, SourceLocation loc,
                 std::vector<std::shared_ptr<Statement>> body);

  void to_string(int indent = 0) override;
  auto evaluate(Environment& environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::vector<std::shared_ptr<Statement>> body_;
};
}  // namespace ctjs::ast
