/**
 * @file calculations.hpp
 * @brief Numerical calculations interface
 * @details Declares functions for performing various numerical calculations
 * on sets of numbers, including distance and similarity calculations.
 */

#pragma once
#include <algorithm>
#include <cstdint>
#include <execution>
#include <numeric>
#include <ranges>

/**
 * @brief Calculates the total distance between corresponding elements in two lists
 * @param leftList First multiset of numbers
 * @param rightList Second multiset of numbers
 * @return Sum of absolute differences between corresponding elements
 */
template <std::ranges::input_range R>
    requires std::integral<std::ranges::range_value_t<R>>
[[nodiscard]] constexpr auto calculateTotalDistance(R const & leftList, R const & rightList) -> uint64_t {
    if (std::ranges::distance(leftList) != std::ranges::distance(rightList)) [[unlikely]] {
        throw std::invalid_argument("Lists must have the same size");
    }

    if (std::is_constant_evaluated()) {
        return std::transform_reduce(std::ranges::begin(leftList), std::ranges::end(leftList),
                                     std::ranges::begin(rightList), uint64_t{0}, std::plus{},
                                     [](auto a, auto b) { return static_cast<uint64_t>(std::abs(a - b)); });
    } else {
        return std::transform_reduce(std::execution::par_unseq, std::ranges::begin(leftList),
                                     std::ranges::end(leftList), std::ranges::begin(rightList), uint64_t{0},
                                     std::plus{},
                                     [](auto a, auto b) { return static_cast<uint64_t>(std::abs(a - b)); });
    }
}

/**
 * @brief Calculates a similarity score between two lists of numbers
 * @param leftList First multiset of numbers
 * @param rightList Second multiset of numbers
 * @return Similarity score based on common elements
 */
template <std::ranges::input_range R>
    requires std::integral<std::ranges::range_value_t<R>>
[[nodiscard]] constexpr auto calculateSimilarityScore(R const & leftList, R const & rightList) -> uint64_t {
    if (std::ranges::distance(leftList) != std::ranges::distance(rightList)) [[unlikely]] {
        throw std::invalid_argument("Lists must have the same size");
    }
    if (std::is_constant_evaluated()) {
        return std::transform_reduce(
            std::ranges::begin(leftList), std::ranges::end(leftList), uint64_t{0}, std::plus{},
            [&](auto const num) { return static_cast<uint64_t>(std::ranges::count(rightList, num) * num); });
    } else {
        return std::transform_reduce(std::execution::par_unseq, std::ranges::begin(leftList),
                                     std::ranges::end(leftList), uint64_t{0}, std::plus{}, [&](auto const num) {
                                         return static_cast<uint64_t>(std::ranges::count(rightList, num) * num);
                                     });
    }
}