#pragma once

#include "expression.h"
#include "pattern.h"

namespace ast {
class Identifier : public Expression, public Pattern {

};
} // namespace ast

