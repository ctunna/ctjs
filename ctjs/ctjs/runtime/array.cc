#include "ctjs/runtime/array.h"

#include "ctjs/runtime/value.h"

namespace ctjs {
auto Array::push(Value value) -> void { elements_.push_back(value); }

auto Array::operator[](int index) -> Value& { return elements_[index]; }

auto Array::elements() const -> const std::vector<Value>& { return elements_; }
}  // namespace ctjs