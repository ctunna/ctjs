#pragma once

#include "block_statement.h"
#include "declaration.h"
#include "identifier.h"

namespace ctjs::ast {
class FunctionDeclaration
    : public Declaration,
      public std::enable_shared_from_this<FunctionDeclaration> {
 public:
  FunctionDeclaration(std::string file_name, SourceLocation loc,
                      std::shared_ptr<Identifier> id,
                      std::vector<std::shared_ptr<Identifier>> params,
                      std::shared_ptr<BlockStatement> body);

  void to_string(int indent = 0) override;
  auto evaluate(std::shared_ptr<Environment> environment) -> Value override;

  auto id() -> std::shared_ptr<Identifier> { return id_; }
  auto params() -> std::vector<std::shared_ptr<Identifier>> { return params_; }
  auto body() -> std::shared_ptr<BlockStatement> { return body_; }

 private:
  std::string file_name_;
  SourceLocation loc_;
  std::shared_ptr<Identifier> id_;
  std::vector<std::shared_ptr<Identifier>> params_;
  std::shared_ptr<BlockStatement> body_;
};
}  // namespace ctjs::ast
