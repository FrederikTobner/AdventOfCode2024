#pragma once

#include <cstdint>
#include <optional>
#include <utility>

namespace aoc::day_13 {
struct result {
    size_t button_a_pushes;
    size_t button_b_pushes;
};

/// @brief Solves a system of equations with two unknowns
/// @details The result is calculated using Cramer's rule in O(1) time
/// @param first_unknown The values of the first unknown
/// @param seond_unknown The values of the second unknown
/// @param expected_result The expected result
/// @return The cheapest result or std::nullopt if no solution exists
std::optional<std::pair<size_t, size_t>>
solveEquationsWithTwoUnknows(aoc::math::vector_2d<size_t> const & first_unknown,
                             aoc::math::vector_2d<size_t> const & seond_unknown,
                             aoc::math::vector_2d<size_t> const & expected_result) {

    double determinant =
        static_cast<double>(first_unknown.x) * seond_unknown.y - static_cast<double>(first_unknown.y) * seond_unknown.x;

    if (determinant == 0) {
        return std::nullopt;
    }

    double a = (static_cast<double>(expected_result.x) * seond_unknown.y -
                static_cast<double>(expected_result.y) * seond_unknown.x) /
               determinant;
    double b = (static_cast<double>(first_unknown.x) * expected_result.y -
                static_cast<double>(first_unknown.y) * expected_result.x) /
               determinant;

    if (a < 0 || b < 0 || a != std::floor(a) || b != std::floor(b)) {
        return std::nullopt;
    }

    size_t result_first_unknown = static_cast<size_t>(a);
    size_t result_second_unknown = static_cast<size_t>(b);

    if (result_first_unknown * first_unknown.x + result_second_unknown * seond_unknown.x != expected_result.x ||
        result_first_unknown * first_unknown.y + result_second_unknown * seond_unknown.y != expected_result.y) {
        return std::nullopt;
    }

    return std::pair<size_t, size_t>{result_first_unknown, result_second_unknown};
}
} // namespace aoc::day_13