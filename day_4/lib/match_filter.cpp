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

/**
 * @brief Determines if a match follows a diagonal pattern
 * @param match The match to analyze
 * @return true if the match coordinates form a diagonal pattern
 */
[[nodiscard]] static bool isDiagonalMatch(word_search::Match const & match);

[[nodiscard]] auto countOverlappingDiagonal(std::vector<word_search::Match> const & matches) -> ptrdiff_t {
    auto sum = aoc::ranges::fold_left(
        matches | std::views::filter(isDiagonalMatch) | std::views::transform([&](auto const & match) {
            return std::ranges::count_if(matches,
                                         [&match](auto const & other) { return hasOverlappingEndpoint(match, other); });
        }),
        static_cast<ptrdiff_t>(0), std::plus<>{});

    return sum / 2;
}

[[nodiscard]] static bool isDiagonalMatch(word_search::Match const & match) {
    return match.coordinates[0].row != match.coordinates[1].row && match.coordinates[0].col != match.coordinates[1].col;
}

[[nodiscard]] static bool hasOverlappingEndpoint(word_search::Match const & match, word_search::Match const & other) {
    bool const is_different_match =
        match.coordinates[0].row != other.coordinates[0].row || match.coordinates[0].col != other.coordinates[0].col;
    bool const has_same_second_pos =
        match.coordinates[1].row == other.coordinates[1].row && match.coordinates[1].col == other.coordinates[1].col;
    return is_different_match && has_same_second_pos;
}

} // namespace aoc::match_filter