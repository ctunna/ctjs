#pragma once

#include <string>
#include <string_view>

namespace ctjs::util::string {

inline auto join(auto begin, auto end, std::string_view delimiter)
    -> std::string {
  std::string result;
  for (auto it = begin; it != end; ++it) {
    result += *it;
    if ((it + 1) != end) {
      result += delimiter;
    }
  }
  return result;
}

}  // namespace ctjs::util::string
