#pragma once

#include <fstream>
#include <string>

namespace ctjs::util::file {
inline auto read_all_text(std::string const& filename) -> std::string {
  std::ifstream file(filename);
  if (!file) {
    throw std::ifstream::failure("Could not open file '" + filename + "'");
  }
  std::string text((std::istreambuf_iterator<char>(file)),
                   std::istreambuf_iterator<char>());
  return text;
}
}  // namespace ctjs::util::file
