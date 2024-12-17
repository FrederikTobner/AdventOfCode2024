#pragma once

#include <cstdint>
#include <vector>

#include "../../shared/src/vector2d.hpp"

#include "cell_type.hpp"

namespace aoc::day_15 {

/// @brief Calculates the gps coordinate of a box
/// @param box The box to calculate the gps coordinate for
/// @return The gps coordinate of the box
auto calculate_gps_coordinate(aoc::math::vector_2d<size_t> const & box) -> size_t;

/// @brief Calculates the sum of the gps coordinates of all boxes in the warehouse
/// @param warehouse The warehouse to calculate the sum for
/// @return The sum of the gps coordinates of all boxes in the warehouse
auto calculate_gps_sum(std::vector<std::vector<cell_type>> & warehouse) -> size_t;

} // namespace aoc::day_15