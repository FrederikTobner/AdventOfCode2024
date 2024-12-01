/**
 * @file ranges_compatibility_layer.hpp
 * @brief Provides compatibility utilities for C++ ranges operations
 * @details This file contains utility functions to work with ranges and convert them
 * to different container types, providing a compatibility layer across different
 * C++ standard library implementations.
 */

#pragma once
#include <ranges>
#include <vector>

/**
 * @brief Compatibility layer for ranges operations
 * @namespace compat
 */
namespace nonstd::ranges {
/**
 * @brief Converts a range to a specified container type
 * @tparam Container The target container type
 * @tparam Range The input range type
 * @param range The range to convert
 * @return A new container of the specified type containing the range elements
 */
template <typename Container, typename Range> [[nodiscard]] auto to_container(Range && range) -> Container {
    Container result;
    for (auto && element : range) {
        result.insert(result.end(), std::forward<decltype(element)>(element));
    }
    return result;
}

/**
 * @brief Converts a range to a vector
 * @tparam Range The input range type
 * @param range The range to convert
 * @return A vector containing the range elements
 */
template <typename Range> [[nodiscard]] auto to_vector(Range && range) {
    return to_container<std::vector<std::ranges::range_value_t<Range>>>(std::forward<Range>(range));
}
} // namespace nonstd::ranges