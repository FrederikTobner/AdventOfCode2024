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
auto parseLine(std::string_view line) -> std::pair<int64_t, int64_t>;

/**
 * @brief Parses the entire input string into two ordered sets of numbers
 * @param input String view containing the entire input
 * @return std::pair of multisets containing the parsed numbers
 * @throws std::invalid_argument if any line parsing fails
 */
auto parseInput(std::string_view input) -> std::pair<std::multiset<int64_t>, std::multiset<int64_t>>;