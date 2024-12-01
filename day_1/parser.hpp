#pragma once
#include <cstdint>
#include <set>
#include <string_view>
#include <utility>

/**
 * @brief Parses a single line containing two space-separated numbers
 * @param line String view containing the line to parse
 * @return std::pair containing the two parsed numbers
 * @throws std::invalid_argument if the conversion to number fails
 */
[[nodiscard]] auto parseLine(std::string_view line) -> std::pair<int64_t, int64_t>;

/**
 * @brief Checks if a string view contains only whitespace characters
 * @param str String view to check
 * @return true if string contains only whitespace or is empty, false otherwise
 */
[[nodiscard]] auto isOnlyWhitespace(std::string_view str) -> bool;

/**
 * @brief Parses the entire input string into two ordered sets of numbers
 * @param input String view containing the entire input
 * @return std::pair of multisets containing the parsed numbers
 * @throws std::invalid_argument if any line parsing fails
 */
[[nodiscard]] auto parseInput(std::string_view input) -> std::pair<std::multiset<int64_t>, std::multiset<int64_t>>;