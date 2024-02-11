#include "source_location.h"

namespace ctjs::ast {
SourceLocation ::SourceLocation(std::string source, Position start,
                                Position end)
    : source(source), start(start), end(end) {}
}  // namespace ctjs::ast
