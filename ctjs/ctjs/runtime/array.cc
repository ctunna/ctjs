#include "ctjs/runtime/array.h"

#include "ctjs/runtime/value.h"

namespace ctjs {
auto Array::push(Value value) -> void { elements_.push_back(value); }

auto Array::operator[](int index) -> Value& { return elements_[index]; }

auto Array::size() const -> size_t { return elements_.size(); }

auto Array::begin() -> std::vector<Value>::iterator {
  return elements_.begin();
}

auto Array::end() -> std::vector<Value>::iterator { return elements_.end(); }

}  // namespace ctjs
