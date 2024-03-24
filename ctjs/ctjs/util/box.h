#pragma once

#include <memory>

namespace ctjs::util {
template <typename T>
class Box {
 public:
  Box(T &&obj) : impl_(new T(std::move(obj))) {}
  Box(const T &obj) : impl_(new T(obj)) {}
  Box(const Box &other) : Box(*other.impl_) {}
  Box(Box &&other) noexcept = default;
  auto operator=(Box &&other) noexcept -> Box & = default;
  auto operator=(const Box &other) -> Box & {
    *impl_ = *other.impl_;
    return *this;
  }
  ~Box() = default;

  auto get() -> T * { return impl_.get(); }

  auto operator*() const -> const T & { return *impl_; }
  auto operator*() -> T & { return *impl_; }
  auto operator->() const -> const T * { return impl_.get(); }
  auto operator->() -> T * { return impl_.get(); }

 private:
  std::unique_ptr<T> impl_;
};
}  // namespace ctjs::util
