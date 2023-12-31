#pragma once

#include <vector>

#include "directive.h"
#include "statement.h"

namespace ast {

template<typename T>
concept DirectiveOrStatement = std::is_same_v<T, Directive> || std::is_same_v<T, Statement>;

template <DirectiveOrStatement T>
class Program : public Node {
public:
  std::vector<T> body;
};

} // namespace ast


