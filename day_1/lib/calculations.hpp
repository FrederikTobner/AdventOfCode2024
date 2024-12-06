/**
 * @file calculations.hpp
 * @brief Header file containing numerical calculation utilities
 * @details Provides template functions for performing numerical calculations
 *          on ranges of numbers, with support for both sequential and parallel
 *          execution. Includes distance and similarity metrics between number sets.
 */

#pragma once
#include <algorithm>
#include <cstdint>
#include <execution>
#include <numeric>
#include <ranges>

/// @brief Namespace containing numerical calculation utilities
namespace aoc::day_1 {

/**
 * @brief Calculates the total distance between corresponding elements in two ranges
 * @tparam RANGE Range type that must satisfy std::ranges::input_range concept
 * @param leftList First range of numbers to compare
 * @param rightList Second range of numbers to compare
 * @return The sum of absolute differences between corresponding elements as uint64_t
 * @note The ranges must contain integral types and be of equal length
 */
template <std::ranges::input_range RANGE>
    requires std::integral<std::ranges::range_value_t<RANGE>>
[[nodiscard]] constexpr auto totalDistance(RANGE const & leftList, RANGE const & rightList) -> uint64_t {
    return std::transform_reduce(std::ranges::begin(leftList), std::ranges::end(leftList),
                                 std::ranges::begin(rightList), uint64_t{0}, std::plus{},
                                 [](auto a, auto b) { return std::abs(a - b); });
}

/**
 * @brief Calculates a similarity score between two ranges of numbers
 * @tparam RANGE Range type that must satisfy std::ranges::input_range concept
 * @param leftList First range of numbers to compare
 * @param rightList Second range of numbers to compare
 * @return A similarity score as uint64_t, where higher values indicate greater similarity
 * @note The score is calculated by summing the products of matching element counts and their values
 */
template <std::ranges::input_range RANGE>
    requires std::integral<std::ranges::range_value_t<RANGE>>
[[nodiscard]] constexpr auto similarityScore(RANGE const & leftList, RANGE const & rightList) -> uint64_t {
    return std::transform_reduce(std::ranges::begin(leftList), std::ranges::end(leftList), uint64_t{0}, std::plus{},
                                 [&](auto const num) { return std::ranges::count(rightList, num) * num; });
}
} // namespace aoc::day_1