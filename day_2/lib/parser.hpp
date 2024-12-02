#pragma once

#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>
#include <vector>

/**
 * @namespace parser
 * @brief Contains functionality for parsing input data into numerical sequences
 */
namespace parser {

/**
 * @brief Parses multi-line input into vectors of numbers
 * @param input String view containing the input data
 * @return Expected containing vector of number sequences or error code on failure
 */
auto parseInput(std::string_view input) -> std::expected<std::vector<std::vector<uint8_t>>, std::error_code>;

/// @brief User-defined literal for creating string views of whitespace characters
/// @param str The string to convert to a string view
/// @param len The length of the string
/// @return A string view of the input string
[[nodiscard]] constexpr auto operator""_ws(char const * str, size_t len) noexcept {
    return std::string_view{str, len};
}

/// @brief String view of whitespace characters for use in parsing
inline constexpr auto WHITESPACE_CHARS = " \t\n\r"_ws;

/**
 * @brief Checks if a string view contains only whitespace characters
 * @param str String view to check
 * @return true if string contains only whitespace or is empty, false otherwise
 */
[[nodiscard]] constexpr auto isOnlyWhitespace(std::string_view str) -> bool {
    return str.empty() || str.find_first_not_of(WHITESPACE_CHARS) == std::string_view::npos;
}

/**
 * @brief Parses a single line into a sequence of numbers
 * @param line String view containing the line to parse
 * @return Expected containing vector of numbers or error code on failure
 * @throws Nothing
 */
auto parseLine(std::string_view line) -> std::expected<std::vector<uint8_t>, std::error_code>;

} // namespace parser