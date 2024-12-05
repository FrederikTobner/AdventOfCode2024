#pragma once

#include <concepts>
#include <cstdint>
#include <ranges>
#include <vector>

namespace aoc::day_5 {

/*!
 * @struct page_ordering_rule
 * @brief Represents a rule that defines the required order between two pages
 */
struct page_ordering_rule {
    /// @brief The page that should appear before the post_page
    uint8_t pre_page;
    /// @brief The page that should appear after the pre_page
    uint8_t post_page;

    /// @brief Default comparison operator
    auto operator<=>(page_ordering_rule const &) const = default;

  private:
};

} // namespace aoc::day_5