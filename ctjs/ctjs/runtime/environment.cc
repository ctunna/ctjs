#include "ctjs/runtime/environment.h"

#include <iostream>

namespace ctjs {
auto Environment::get(std::string const& name) const -> Value {
  return scope_.at(name);
}

void Environment::set(std::string const& name, Value value) {
  scope_.insert_or_assign(name, value);
}

void Environment::to_string() {
  for (auto const& [name, value] : scope_) {
    std::cout << name << " = " << value.to_string() << std::endl;
  }
}
}  // namespace ctjs
