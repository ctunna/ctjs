#include "ctjs/runtime/object.h"

#include "ctjs/runtime/value.h"

namespace ctjs {
auto Object::get_property(const std::string_view name) const -> Value {
  auto it = properties_.find(std::string(name));
  if (it == properties_.end()) {
    return Value();
  }
  return it->second;
}

void Object::set_property(const std::string_view name, const Value& value) {
  properties_[std::string(name)] = value;
}

auto Object::operator[](const std::string_view name) -> Value& {
  return properties_[std::string(name)];
}

auto Object::has_property(const std::string_view name) const -> bool {
  return properties_.find(std::string(name)) != properties_.end();
}

auto Object::properties() const
    -> const std::unordered_map<std::string, Value>& {
  return properties_;
}

}  // namespace ctjs
