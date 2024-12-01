#pragma once
#include <ranges>
#include <vector>

/**
 * @brief Compatibility layer for ranges operations
 * @namespace compat
 */
namespace compat {
/**
 * @brief Converts a range to a specified container type
 * @tparam Container The target container type
 * @tparam Range The input range type
 * @param rng The range to convert
 * @return A new container of the specified type containing the range elements
 */
template <typename Container, typename Range> [[nodiscard]] auto to_container(Range && rng) -> Container {
    Container result;
    for (auto && element : rng) {
        result.insert(result.end(), std::forward<decltype(element)>(element));
    }
    return result;
}

/**
 * @brief Converts a range to a vector
 * @tparam Range The input range type
 * @param rng The range to convert
 * @return A vector containing the range elements
 */
template <typename Range> [[nodiscard]] auto to_vector(Range && rng) {
    return to_container<std::vector<std::ranges::range_value_t<Range>>>(std::forward<Range>(rng));
}
} // namespace compat