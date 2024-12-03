/**
 * @file ranges_compatibility_layer.hpp
 * @brief Provides compatibility utilities for C++ ranges operations
 * @details This file contains utility functions to work with ranges and convert them
 * to different container types, providing a compatibility layer across different
 * C++ standard library implementations. Currently supports conversion to std::string and std::vector.
 */

#pragma once
#include <ranges>
#include <string>
#include <type_traits>
#include <vector>

/**
 * @brief Compatibility layer for ranges operations
 * @namespace nonstd::ranges
 */
namespace nonstd::ranges {

template <typename Container> struct container_traits {
    static void reserve(Container & c, size_t) {
    }
};

template <> struct container_traits<std::string> {
    using value_type = char;
    static void reserve(std::string & c, size_t size) {
        c.reserve(size);
    }
};

template <> struct container_traits<std::vector<std::string>> {
    static void reserve(std::vector<std::string> & c, size_t size) {
        c.reserve(size);
    }
};

/**
 * @brief Converts a range to a specified container type
 * @tparam Container The target container type
 * @tparam Range The input range type
 * @param range The range to convert
 * @return A new container of the specified type containing the range elements
 */
template <typename Container, typename Range> [[nodiscard]] auto to_container(Range && range) -> Container {
    Container result;
    if constexpr (requires { container_traits<Container>::reserve(result, std::ranges::size(range)); }) {
        container_traits<Container>::reserve(result, std::ranges::size(range));
    }
    for (auto && element : range) {
        if constexpr (std::is_same_v<Container, std::string>) {
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
template <typename Container> struct to_t {
    template <std::ranges::range Range> friend Container operator|(Range && range, to_t) {
        return to_container<Container>(std::forward<Range>(range));
    }
};

/**
 * @brief Helper variable template for pipe syntax
 */
template <typename Container> inline constexpr to_t<Container> to{};

/**
 * @brief Converts a range to a vector
 * @tparam Range The input range type
 * @param range The range to convert
 * @return A vector containing the range elements
 */
template <typename Range> [[nodiscard]] auto to_vector(Range && range) {
    return to_container<std::vector<std::ranges::range_value_t<Range>>>(std::forward<Range>(range));
}

template <typename Range> [[nodiscard]] auto to_string(Range && range) -> std::string {
    std::string result;
    if constexpr (requires { result.resize(std::ranges::size(range)); }) {
        result.resize(std::ranges::size(range));
        std::ranges::copy(range, result.begin());
    } else {
        result.reserve(std::ranges::distance(range));
        std::ranges::copy(range, std::back_inserter(result));
    }
    return result;
}

/**
 * @brief Pipe operator for range-to-container conversion
 * @tparam Container The target container type
 * @tparam Range The input range type
 */
template <typename Container> struct to_helper {
    template <std::ranges::range Range> friend Container operator|(Range && range, to_helper const &) {
        return to_container<Container>(std::forward<Range>(range));
    }
};

/**
 * @brief Pipe operator for range-to-container conversion
 */
template <std::ranges::range Range, typename Container> Container operator|(Range && range, to_t<Container>) {
    return to_container<Container>(std::forward<Range>(range));
}

} // namespace nonstd::ranges