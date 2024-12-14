#pragma once

#include <cstdint>
#include <string_view>
#include <vector>

namespace aoc::day_13 {

#define BUTTON_A_PUSH_COST 3
#define BUTTON_B_PUSH_COST 1

[[nodiscard]] auto calculateTotalPrice(std::vector<std::string_view> lines, size_t const & increment) -> size_t;

} // namespace aoc::day_13