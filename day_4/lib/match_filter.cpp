#include "match_filter.hpp"

#include <algorithm>
#include <execution>
#include <ranges>

#include "../../shared/src/ranges_compatibility_layer.hpp"

namespace aoc::day_4 {

/**
 * @brief Checks if two matches have an overlapping endpoint
 * @param match The first match to compare
 * @param other The second match to compare
 * @return true if the matches have different starting points but the same endpoint
 */
[[nodiscard]] static bool hasOverlappingEndpoint(match const & first, match const & second);

/// @brief Checks if two matches form an overlapping pair
/// @param first The first match to compare
/// @param second The second match to compare
/// @return true if the matches form an overlapping pair
[[nodiscard]] static bool formsOverlappingPair(match const & first, match const & second);

/**
 * @brief Determines if a match follows a diagonal pattern
 * @param match The match to analyze
 * @return true if the match coordinates form a diagonal pattern
 */
[[nodiscard]] static bool isDiagonalMatch(match const & m);

[[nodiscard]] auto countOverlappingDiagonal(std::vector<match> const & matches) -> ptrdiff_t {
    auto diagonal_matches = matches | std::views::filter(isDiagonalMatch);
    return std::ranges::count_if(diagonal_matches, [&](auto const & first) {
        return std::ranges::any_of(diagonal_matches,
                                   [&](auto const & second) { return formsOverlappingPair(first, second); });
    });
}

[[nodiscard]] static bool formsOverlappingPair(match const & first, match const & second) {
    return first.coordinates[0] < second.coordinates[0] && hasOverlappingEndpoint(first, second);
}

[[nodiscard]] static bool isDiagonalMatch(match const & mth) {
    return mth.coordinates[0].row != mth.coordinates[1].row && mth.coordinates[0].col != mth.coordinates[1].col;
}

[[nodiscard]] static bool hasOverlappingEndpoint(match const & first, match const & second) {
    return (std::tie(first.coordinates[0].row, first.coordinates[0].col) !=
            std::tie(second.coordinates[0].row, second.coordinates[0].col)) &&
           (std::tie(first.coordinates[1].row, first.coordinates[1].col) ==
            std::tie(second.coordinates[1].row, second.coordinates[1].col));
}

} // namespace aoc::day_4