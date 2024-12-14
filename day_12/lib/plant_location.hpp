#pragma once

#include <cstdint>
#include <unordered_set>
#include <vector>

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_12 {

[[nodiscard]] auto splitIntoConnectedLocations(std::unordered_set<aoc::math::vector_2d<int16_t>> const & locations)
    -> std::vector<std::unordered_set<aoc::math::vector_2d<int16_t>>>;

[[nodiscard]] auto calculateFencePrice(std::unordered_set<aoc::math::vector_2d<int16_t>> const & locations) -> size_t;

[[nodiscard]] auto calculateFencePrice2(std::unordered_set<aoc::math::vector_2d<int16_t>> const & locations) -> size_t;

} // namespace aoc::day_12
