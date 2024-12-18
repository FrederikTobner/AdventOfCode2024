#pragma once

#include <expected>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"
#include "program.hpp"


namespace aoc::day_17 {

/// @brief Parses input text into a program structure
/// @param input String view containing the program text
/// @return Expected containing either the parsed program or an error code
/// @throws std::invalid_argument If the opcode format is invalid
/// @details The input format should be:
/// RegisterA: <value>
/// RegisterB: <value>
/// RegisterC: <value>
///
/// Opcode:<value1>,<value2>,...
[[nodiscard]] auto parse_program(std::string_view input) -> std::expected<program, std::error_code>;

} // namespace aoc::day_17