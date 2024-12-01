/**
 * @file parser.hpp
 * @brief Input parsing functionality declarations
 * @details Provides interfaces for parsing input data containing pairs of numbers.
 * Includes utilities for parsing individual lines and complete input files,
 * with error handling through std::expected.
 */

#pragma once

#include <cstdint>
#include <expected>
#include <set>
#include <string_view>
#include <system_error>
#include <utility>

namespace parser {
    // Modern string literal operator
    constexpr auto operator""_ws(char const* str, size_t len) noexcept {
        return std::string_view{str, len};
    }

    inline constexpr auto WHITESPACE_CHARS = " \t\n\r"_ws;

    /**
     * @brief Parses a single line containing two space-separated numbers
     * @param line String view containing the line to parse
     * @return std::pair containing the two parsed numbers
     * @throws std::invalid_argument if the conversion to number fails
     */
    [[nodiscard]] auto parseLine(std::string_view line) -> std::expected<std::pair<int64_t, int64_t>, std::error_code>;

    /**
     * @brief Checks if a string view contains only whitespace characters
     * @param str String view to check
     * @return true if string contains only whitespace or is empty, false otherwise
     */
    [[nodiscard]] constexpr auto isOnlyWhitespace(std::string_view str) -> bool {
        return str.empty() || str.find_first_not_of(WHITESPACE_CHARS) == std::string_view::npos;
    }

    /**
     * @brief Parses the entire input string into two ordered sets of numbers
     * @param input String view containing the entire input
     * @return std::pair of multisets containing the parsed numbers
     * @throws std::invalid_argument if any line parsing fails
     */
    [[nodiscard]] auto parseInput(std::string_view input)
        -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code>;

    /**
     * @brief Checks if a character is considered whitespace
     * @param c Character to check
     * @return true if the character is whitespace, false otherwise
     * @note Whitespace characters include space, tab, newline and carriage return
     */
    [[nodiscard]] constexpr auto isWhitespace(char c) noexcept -> bool {
        return WHITESPACE_CHARS.contains(c);  // C++23 contains
    }
}