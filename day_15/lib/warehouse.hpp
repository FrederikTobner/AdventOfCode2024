#pragma once

#include <vector>

#include "cell_type.hpp"

#include "../../shared/src/direction.hpp"

namespace aoc::day_15 {

/// @brief Executes multiple moves on the warehouse
/// @param warehouse The warehouse where the moves are executed on
/// @param moves The moves that are executed
auto executeMoves(std::vector<std::vector<cell_type>> & warehouse, std::vector<aoc::math::Direction> const & moves)
    -> void;

} // namespace aoc::day_15