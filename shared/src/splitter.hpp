#pragma once

#include "ranges_compatibility_layer.hpp"

namespace aoc::splitter {

/// @brief User-defined literal for creating string views of whitespace characters
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
 * @brief Normalizes tabs by replacing them with spaces
 * @param str String view to process
 * @return String with tabs replaced by spaces
 */
[[nodiscard]] inline auto normalizeTabs(std::string_view str) -> std::string {
    return str | std::views::transform([](char c) { return c == '\t' ? ' ' : c; }) | aoc::ranges::to<std::string>;
}

} // namespace aoc::splitter