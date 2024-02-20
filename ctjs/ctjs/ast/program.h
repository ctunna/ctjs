#pragma once

#include <vector>

#include "ctjs/ast/directive.h"
#include "ctjs/ast/source_location.h"
#include "ctjs/ast/statement.h"

namespace ctjs::ast {
class Program : public Node {
 public:
  Program(std::string file_name, SourceLocation loc,
          std::vector<std::shared_ptr<Statement>> body);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::vector<std::shared_ptr<Statement>> body_;
};
}  // namespace ctjs::ast
