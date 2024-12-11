/**
 * @file ranges_compatibility_layer.hpp
 * @brief Provides compatibility utilities for C++ ranges operations
 * @details This file contains utility functions to work with ranges and convert them
 * to different container types, providing a compatibility layer across different
 * C++ standard library implementations. Currently supports conversion to std::string and std::vector.
 */

#pragma once
#include <algorithm>
#include <cstdint>
#include <execution>
#include <ranges>
#include <string>
#include <type_traits>
#include <vector>

#include "container_traits.hpp"

/**
 * @brief Compatibility layer for ranges operations
 * @namespace aoc::ranges
 */
namespace aoc::ranges {

template <typename CONTAINER>
concept has_reverve = requires(CONTAINER & container, size_t size) {
    aoc::container::container_traits<CONTAINER>::reserve(container, size);
};

template <typename RANGE>
concept has_size = requires(RANGE range) { std::ranges::size(range); };

/**
 * @brief Converts a range to a specified container type
 * @tparam Container The target container type
 * @tparam Range The input range type
 * @param range The range to convert
 * @return A new container of the specified type containing the range elements
 */
template <typename CONTAINER, typename RANGE> [[nodiscard]] auto to_container(RANGE && range) -> CONTAINER {
    CONTAINER result;
    if constexpr (has_reverve<CONTAINER> && has_size<RANGE>) {
        auto range_size = std::ranges::size(range);
        if (range_size <= SIZE_MAX) {
            aoc::container::container_traits<CONTAINER>::reserve(result, (size_t)range_size);
        } else {
            aoc::container::container_traits<CONTAINER>::reserve(result, SIZE_MAX);
        }
    }
    for (auto && element : range) {
        if constexpr (std::is_same_v<CONTAINER, std::string>) {
            result.push_back(element);
        } else {
            result.insert(result.end(), std::forward<decltype(element)>(element));
        }
    }
    return result;
}

/**
 * @brief Helper struct for pipe syntax support
 */
template <typename CONTAINER> struct Converter {
    template <std::ranges::range RANGE> friend CONTAINER operator|(RANGE && range, Converter) {
        return to_container<CONTAINER>(std::forward<RANGE>(range));
    }
};

/**
 * @brief Converts a range to a specified container type - only needed under GCC 13 because ranges::to is not
 * implemented yet
 */
template <typename CONTAINER> inline constexpr Converter<CONTAINER> to{};

/**
 * @brief Converts a range to a vector
 * @tparam Range The input range type
 * @param range The range to convert
 * @return A vector containing the range elements
 */
template <typename RANGE> [[nodiscard]] auto to_vector(RANGE && range) {
    return to_container<std::vector<std::ranges::range_value_t<RANGE>>>(std::forward<RANGE>(range));
}

template <typename Range> [[nodiscard]] auto to_string(Range && range) -> std::string {
    std::string result;
    result.resize(std::ranges::size(range));
    std::ranges::copy(range, result.begin());
    return result;
}

/**
 * @brief Pipe operator for range-to-container conversion
 * @tparam Container The target container type
 * @tparam Range The input range type
 */
template <typename CONTAINER> struct ConversionHelper {
    template <std::ranges::range RANGE> friend CONTAINER operator|(RANGE && range, ConversionHelper const &) {
        return to_container<CONTAINER>(std::forward<RANGE>(range));
    }
};

/**
 * @brief Pipe operator for range-to-container conversion
 */
template <std::ranges::range RANGE, typename CONTAINER> CONTAINER operator|(RANGE && range, Converter<CONTAINER>) {
    return to_container<CONTAINER>(std::forward<RANGE>(range));
}

} // namespace aoc::ranges