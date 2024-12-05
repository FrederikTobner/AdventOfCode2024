#pragma once

#include <span>
#include <string_view>
#include <vector>

/**
 * @file word_search.hpp
 * @brief Word search puzzle solver implementation
 * @details Provides functionality to find words in a 2D grid of characters,
 *          supporting horizontal, vertical, and diagonal word patterns
 */

namespace aoc::day_4 {

/**
 * @struct position
 * @brief Represents a position in the 2D grid
 */
struct position {
    size_t row; ///< Row index in the grid
    size_t col; ///< Column index in the grid

    [[nodiscard]] auto operator<=>(position const &) const = default;
};

/**
 * @struct match
 * @brief Represents a found word match in the grid
 */
struct match {
    std::vector<position> coordinates; ///< Sequence of positions forming the matched word
};

/**
 * @brief Searches for all occurrences of a word in the grid
 * @param grid The 2D character grid to search in
 * @param word The word to search for
 * @return Vector of match objects containing all found occurrences
 */
[[nodiscard]] auto findWord(std::span<std::string_view const> grid, std::string_view word) -> std::vector<match>;

} // namespace aoc::day_4