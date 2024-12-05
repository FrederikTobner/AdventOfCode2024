#pragma once

#include <expected>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "../../shared/src/ranges_compatibility_layer.hpp"

/**
 * @file grid_processor.hpp
 * @brief Provides utilities for processing and validating 2D character grids
 * @details Contains functionality to process input strings into grid format
 *          and validate grid consistency
 */

/**
 * @namespace aoc::day_4
 * @brief Contains the code for Day 4 puzzle solutions
 */
namespace aoc::day_4 {

/**
 * @brief Processes input string into lines suitable for grid operations
 * @param input Raw input string containing newline-separated grid rows
 * @return Vector of string_views representing grid rows with normalized line endings
 */
[[nodiscard]] auto processLines(std::string const & input) -> std::vector<std::string_view>;

/**
 * @brief Validates that all rows in the grid have the same length
 * @param lines Span of string_views representing grid rows
 * @return true if all rows have equal length, false otherwise
 */
[[nodiscard]] auto validateGrid(std::span<std::string_view const> lines) -> bool;

} // namespace aoc::day_4