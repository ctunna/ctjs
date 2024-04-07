#include "ctjs/runtime/environment.h"

#include <iostream>

namespace ctjs {
Environment::Environment(Environment* parent) : parent_(parent) {}

auto Environment::get(std::string const& name) const -> Value {
  if (scope_.contains(name)) {
    return scope_.at(name);
  }
  if (parent_) {
    return parent_->get(name);
  }
  return Value();
}

void Environment::define(std::string const& name, Value value) {
  scope_.insert_or_assign(name, value);
}

void Environment::set(std::string const& name, Value value) {
  if (scope_.contains(name)) {
    scope_.insert_or_assign(name, value);
  } else if (parent_) {
    parent_->set(name, value);
  } else {
    throw std::runtime_error("Undefined variable: " + name);
  }
}

void Environment::print() {
  for (auto const& [name, value] : scope_) {
    std::cout << name << " = " << value.to_string() << std::endl;
  }
}
}  // namespace ctjs
