#pragma once

#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>
#include <vector>

namespace aoc::day_18 {

/// @brief Parses the input file containing coordinate pairs
/// @param filename Path to the input file
/// @return Vector of coordinate pairs on success, error code on failure
auto parseInput(std::string_view filename) -> std::expected<std::vector<std::vector<int16_t>>, std::error_code>;

} // namespace aoc::day_18