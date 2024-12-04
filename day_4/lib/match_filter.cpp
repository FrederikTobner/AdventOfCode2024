#include "match_filter.hpp"

#include <algorithm>
#include <execution>
#include <ranges>

#include "../../shared/src/ranges_compatibility_layer.hpp"

namespace aoc::match_filter {

/**
 * @brief Checks if two matches have an overlapping endpoint
 * @param match The first match to compare
 * @param other The second match to compare
 * @return true if the matches have different starting points but the same endpoint
 */
[[nodiscard]] static bool hasOverlappingEndpoint(word_search::Match const & match, word_search::Match const & other);

/// @brief Checks if two matches form an overlapping pair
/// @param first The first match to compare
/// @param second The second match to compare
/// @return true if the matches form an overlapping pair
[[nodiscard]] static bool formsOverlappingPair(word_search::Match const & first, word_search::Match const & second);

/**
 * @brief Determines if a match follows a diagonal pattern
 * @param match The match to analyze
 * @return true if the match coordinates form a diagonal pattern
 */
[[nodiscard]] static bool isDiagonalMatch(word_search::Match const & match);

[[nodiscard]] auto countOverlappingDiagonal(std::vector<word_search::Match> const & matches) -> ptrdiff_t {
    auto diagonal_matches = matches | std::views::filter(isDiagonalMatch);
    return std::ranges::count_if(diagonal_matches, [&](auto const & match1) {
        return std::ranges::any_of(diagonal_matches,
                                   [&](auto const & match2) { return formsOverlappingPair(match1, match2); });
    });
}

[[nodiscard]] static bool formsOverlappingPair(word_search::Match const & first, word_search::Match const & second) {
    return first.coordinates[0] < second.coordinates[0] && hasOverlappingEndpoint(first, second);
}

[[nodiscard]] static bool isDiagonalMatch(word_search::Match const & match) {
    return match.coordinates[0].row != match.coordinates[1].row && match.coordinates[0].col != match.coordinates[1].col;
}

[[nodiscard]] static bool hasOverlappingEndpoint(word_search::Match const & match, word_search::Match const & other) {
    return (std::tie(match.coordinates[0].row, match.coordinates[0].col) !=
            std::tie(other.coordinates[0].row, other.coordinates[0].col)) &&
           (std::tie(match.coordinates[1].row, match.coordinates[1].col) ==
            std::tie(other.coordinates[1].row, other.coordinates[1].col));
}

} // namespace aoc::match_filter