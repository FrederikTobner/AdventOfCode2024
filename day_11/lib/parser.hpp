#pragma once

#include <cstddef>
#include <expected>
#include <system_error>
#include <vector>

#include "parsing_error.hpp"

namespace aoc::day_11 {

/// @brief Parses a string of numbers into a vector of size_t values
/// @param input The input string to parse
/// @return A vector of size_t values, or an error code on failure
auto parseNumbers(std::string_view input) -> std::expected<std::vector<size_t>, std::error_code>;

} // namespace aoc::day_11