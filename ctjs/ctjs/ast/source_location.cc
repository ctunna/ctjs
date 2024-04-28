#include "ctjs/ast/source_location.h"

#include <utility>

namespace ctjs::ast {
SourceLocation ::SourceLocation(std::string source, Position start,
                                Position end)
    : source(std::move(source)), start(start), end(end) {}
}  // namespace ctjs::ast
