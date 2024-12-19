#pragma once

#include <expected>
#include <string>
#include <system_error>
#include <vector>

namespace aoc::day_19 {

/// @brief Contains parsed puzzle input data
struct puzzle_input {
    std::vector<std::string> patterns; ///< List of pattern strings
    std::vector<std::string> designs;  ///< List of design strings to match against
};

/// @brief Parses the raw puzzle input into structured data
/// @param input Raw puzzle input string
/// @return Expected containing puzzle_input on success, error_code on failure
[[nodiscard]] auto parseInput(std::string_view input) -> std::expected<puzzle_input, std::error_code>;

} // namespace aoc::day_19
