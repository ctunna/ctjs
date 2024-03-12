#pragma once

#include <string>
#include <vector>

#include "ctjs/ast/identifier.h"
#include "ctjs/ast/expression.h"
#include "ctjs/ast/source_location.h"

namespace ctjs::ast {
class Property {
 public:
  Property(IdentifierPtr key, ExpressionPtr value);

  IdentifierPtr const key;
  ExpressionPtr const value;
};

class ObjectExpression {
 public:
  ObjectExpression(std::string file_name, SourceLocation loc,
                   std::vector<Property> properties);

  std::string const file_name;
  SourceLocation const loc;
  std::vector<Property> const properties;
};
}