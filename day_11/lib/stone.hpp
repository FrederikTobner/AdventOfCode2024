#pragma once

#include <cstddef>
#include <vector>

#include "../../shared/src/print_compatibility_layer.hpp"

namespace aoc::day_11 {

/// @brief Calculate total stones after given number of cycles
/// @param stones The initial stone counts
/// @param cycles The number of cycles to run
/// @return The total number of stones after the given number of cycles
auto calculateStones(std::vector<size_t> const & stones, size_t const cycles) -> size_t;

} // namespace aoc::day_11