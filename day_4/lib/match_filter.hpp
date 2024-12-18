#pragma once

#include "word_search.hpp"
#include <vector>

/**
 * @file match_filter.hpp
 * @brief Provides filtering and analysis functionality for word search matches
 * @details Contains utilities to analyze and filter word search matches,
 *          particularly focusing on diagonal and overlapping patterns
 */

namespace aoc::day_4 {

/**
 * @brief Counts the number of overlapping diagonal matches
 * @param matches Vector of matches to analyze
 * @return Number of overlapping diagonal matches, where overlapping pairs are counted once
 */
[[nodiscard]] auto countOverlappingDiagonal(std::vector<match> const & matches) -> ptrdiff_t;

} // namespace aoc::day_4