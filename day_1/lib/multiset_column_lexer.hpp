/**
 * @file multiset_column_lexer.hpp
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

/// @brief Namespace containing input parsing utilities
namespace aoc::lexer {

/// @brief Processing mode for input parsing - mainly used for performance testing optimizations made using parallelism
enum class ProcessingMode {
    Sequential,
    Parallel
};

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
 * @brief Parses a single line containing two space-separated numbers
 * @param line String view containing the line to parse
 * @return std::pair containing the two parsed numbers
 * @throws std::invalid_argument if the conversion to number fails
 */
[[nodiscard]] auto tokenizeLine(std::string_view line) -> std::expected<std::pair<int64_t, int64_t>, std::error_code>;

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
 * @param mode Processing mode to use for parsing - defaults to Parallel
 * @return std::pair of multisets containing the parsed numbers
 * @throws std::invalid_argument if any line parsing fails
 */
[[nodiscard]] auto tokenize(std::string_view input, ProcessingMode mode = ProcessingMode::Parallel)
    -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code>;

/**
 * @brief Normalizes tab characters by replacing them with two spaces
 * @param str String view to process
 * @return String with tabs replaced by two spaces
 */
[[nodiscard]] auto normalizeTabs(std::string_view str) -> std::string;

} // namespace aoc::lexer