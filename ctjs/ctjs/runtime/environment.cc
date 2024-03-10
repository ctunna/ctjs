#include "ctjs/runtime/environment.h"

#include <iostream>

namespace ctjs {
Environment::Environment(std::shared_ptr<Environment> parent)
    : parent_(std::move(parent)) {}

auto Environment::get(std::string const& name) const -> Value {
  if (scope_.contains(name)) {
    return scope_.at(name);
  }
  if (parent_) {
    return parent_->get(name);
  }
  return Value();
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
