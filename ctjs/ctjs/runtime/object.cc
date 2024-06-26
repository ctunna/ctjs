#include "ctjs/runtime/object.h"

#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include "ctjs/runtime/value.h"
#include "ctjs/util/string/join.h"

namespace ctjs {
auto Object::get_property(const std::string_view name) -> Value {
  auto iter = properties_.find(name);
  if (iter == properties_.end()) {
    return {};
  }
  return iter->second;
}

void Object::set_property(const std::string_view name, Value value) {
  properties_[std::string(name)] = std::move(value);
}

auto Object::operator[](const std::string_view name) -> Value& {
  return properties_.at(std::string(name));
}

auto Object::has_property(const std::string_view name) const -> bool {
  return properties_.find(name) != properties_.end();
}

auto Object::properties() const
    -> std::map<std::string, Value, std::less<>> const& {
  return properties_;
}

auto Object::begin() -> std::map<std::string, Value>::iterator {
  return properties_.begin();
}

auto Object::end() -> std::map<std::string, Value>::iterator {
  return properties_.end();
}

auto Object::to_string() const -> std::string {
  std::vector<std::string> strings;
  auto props{properties()};
  std::transform(props.begin(), props.end(), std::back_inserter(strings),
                 [](auto const& pair) {
                   return pair.first + ": " + pair.second.to_string();
                 });
  auto object{ctjs::util::string::join(strings.begin(), strings.end(), ", ")};
  return "{" + object + "}";
}

}  // namespace ctjs
