#pragma once

#include <expected>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "program.hpp"

#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

namespace aoc::day_17 {

[[nodiscard]] auto parse_program(std::string_view input) -> std::expected<program, std::error_code>;

} // namespace aoc::day_17