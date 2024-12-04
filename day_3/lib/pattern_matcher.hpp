#pragma once

/**
 * @file pattern_matcher.hpp
 * @brief Contains utilities for finding multiplication pairs in text patterns
 */

#include <cstdint>
#include <string_view>
#include <utility>
#include <vector>


namespace aoc::pattern_matcher {

/**
 * @brief Finds pairs of numbers that should be multiplied based on pattern matching
 * @param text Input text to analyze
 * @return Vector of pairs containing numbers to be multiplied
 */
[[nodiscard]] auto findMultiplicationPairs(std::string_view text) -> std::vector<std::pair<uint16_t, uint16_t>>;

/**
 * @brief Finds pairs of numbers using an alternate pattern matching algorithm with toggle mechanism
 * @param text Input text to analyze
 * @return Vector of pairs containing numbers to be multiplied
 */
[[nodiscard]] auto findMultiplicationPairsWithToggle(std::string_view text)
    -> std::vector<std::pair<uint16_t, uint16_t>>;

} // namespace aoc::pattern_matcher