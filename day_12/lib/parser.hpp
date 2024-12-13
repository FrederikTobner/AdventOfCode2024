#pragma once

#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>
#include <unordered_map>
#include <unordered_set>

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_12 {
auto parseInput(std::string_view input)
    -> std::expected<std::unordered_map<char, std::unordered_set<aoc::math::vector_2d<int16_t>>>, std::error_code>;
} // namespace aoc::day_12