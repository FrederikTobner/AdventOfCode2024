#pragma once

#include <cstdint>
#include <optional>
#include <vector>

/*!
 * @namespace aoc::day_5
 * @brief Namespace containing solutions for Advent of Code 2024 Day 5
 *        Implementation focuses on page ordering and validation systems
 */
namespace aoc::day_5 {

/*!
 * @struct page_update
 * @brief Represents a collection of page values that can be updated
 */
struct page_update {
    //! The collection of page values to be updated
    std::vector<uint8_t> updateValues;

    /*!
     * @brief Gets the middle element from the update values
     * @return The middle element if it exists, std::nullopt otherwise
     */
    [[nodiscard]] std::optional<uint8_t> getMiddleElement() const;
};
} // namespace aoc::day_5
