#pragma once

#include <cstddef>
#include <expected>
#include <system_error>
#include <vector>

namespace aoc::day_11 {

auto parseNumbers(std::string_view input) -> std::expected<std::vector<size_t>, std::error_code>;

} // namespace aoc::day_11