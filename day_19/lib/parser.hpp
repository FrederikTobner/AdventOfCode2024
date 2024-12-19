#pragma once

#include <expected>
#include <string>
#include <system_error>
#include <vector>

namespace aoc::day_19 {

struct puzzle_input {
    std::vector<std::string> patterns;
    std::vector<std::string> designs;
};

[[nodiscard]] auto parseInput(std::string_view input) -> std::expected<puzzle_input, std::error_code>;

} // namespace aoc::day_19
