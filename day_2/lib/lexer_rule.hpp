#pragma once

#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>

/**
 * @namespace parser
 * @brief Contains functionality for parsing input data into numerical sequences
 */
namespace aoc::lexer::rules {

auto handleToken(std::string_view token) -> std::expected<uint8_t, std::error_code>;

} // namespace aoc::lexer::rules