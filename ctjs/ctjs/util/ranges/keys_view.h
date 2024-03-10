#pragma once

#include <iostream>
#include <ranges>
#include <unordered_map>

namespace ctjs::util::ranges {
template <typename Map>
class MapKeyView : public std::ranges::view_interface<MapKeyView<Map>> {
  const Map& map_;

 public:
  MapKeyView(const Map& map) : map_(map) {}

  auto begin() const {
    return map_ |
           std::views::transform([](const auto& pair) { return pair.first; });
  }

  auto end() const {
    return map_ |
           std::views::transform([&](const auto&) { return std::end(map_); });
  }
};
}  // namespace ctjs::util::ranges
