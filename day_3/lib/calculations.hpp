#pragma once

/**
 * @file calculations.hpp
 * @brief Provides utilities for numerical calculations and accumulations
 */

#include <concepts>
#include <cstdint>
#include <ranges>
#include <utility>
#include <vector>

#include "../../shared/src/ranges_compatibility_layer.hpp"

namespace aoc::day_3 {

/**
 * @brief Concept that constrains types to numeric types (integral or floating point)
 * @tparam T Type to check
 */
template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

/**
 * @brief Accumulates the products of pairs in parallel
 * @tparam T The numeric type to use for accumulation (defaults to uint64_t)
 * @param matches Range of pairs to process
 * @return Sum of all products of the pairs
 */
template <Numeric T = uint64_t> [[nodiscard]] auto accumulateProducts(std::ranges::range auto const & matches) {
    return std::transform_reduce(
        std::execution::par_unseq, std::ranges::begin(matches), std::ranges::end(matches), T{0}, std::plus<T>{},
        [](auto const & pair) -> T { return static_cast<T>(pair.first) * static_cast<T>(pair.second); });
}

} // namespace aoc::day_3