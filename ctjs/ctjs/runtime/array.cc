#include "ctjs/runtime/array.h"

#include <algorithm>

#include "ctjs/runtime/value.h"
#include "ctjs/util/string/join.h"

namespace ctjs {
auto Array::push(Value value) -> void {
  set_property(std::to_string(size_++), std::move(value));
}

auto Array::operator[](const size_t index) -> Value {
  return get_property(std::to_string(index));
}

auto Array::size() const -> size_t { return size_; }

auto Array::to_string() const -> std::string {
  std::vector<std::string> strings;
  auto props{properties()};
  std::transform(props.begin(), props.end(), std::back_inserter(strings),
                 [](auto const& v) { return v.second.to_string(); });
  auto array{ctjs::util::string::join(strings.begin(), strings.end(), ", ")};
  return "[" + array + "]";
}

}  // namespace ctjs
