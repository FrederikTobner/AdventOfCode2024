#pragma once

#include <expected>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

#include "../../shared/src/direction.hpp"

#include "cell_type.hpp"

namespace aoc::day_15 {

/// @brief Parses the input into a pair of warehouse and movements
/// @param input The input to parse
/// @return A pair of warehouse and movements
auto parse_input(std::string_view input)
    -> std::expected<std::pair<std::string_view, std::string_view>, std::error_code>;

/// @brief Parses the warehouse from the input
/// @param input The input to parse
/// @return The parsed warehouse
auto parse_warehouse(std::string_view input) -> std::vector<std::vector<cell_type>>;

/// @brief Parses the movements from the input
/// @param input The input to parse
/// @return The parsed movements
auto parse_movements(std::string_view input) -> std::vector<aoc::math::Direction>;

} // namespace aoc::day_15