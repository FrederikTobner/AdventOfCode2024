#pragma once

#include <cstdint>
#include <optional>
#include <utility>

#include "vector2d.hpp"

namespace aoc::math {

/// @brief Solves a system of equations with two unknowns
/// @details The result is calculated using Cramer's rule in O(1) time
/// @param first_unknown The values of the first unknown
/// @param seond_unknown The values of the second unknown
/// @param expected_result The expected result
/// @return The cheapest result or std::nullopt if no solution exists
auto solveEquationsWithTwoUnknows(aoc::math::vector_2d<size_t> const & first_unknown,
                                  aoc::math::vector_2d<size_t> const & seond_unknown,
                                  aoc::math::vector_2d<size_t> const & expected_result)
    -> std::optional<std::pair<size_t, size_t>>;
} // namespace aoc::math