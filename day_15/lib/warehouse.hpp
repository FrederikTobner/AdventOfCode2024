#pragma once

#include <vector>

#include "cell_type.hpp"

#include "../../shared/src/direction.hpp"

namespace aoc::day_15 {

auto executeMoves(std::vector<std::vector<cell_type>> & warehouse, std::vector<aoc::math::Direction> const & moves)
    -> void;

} // namespace aoc::day_15