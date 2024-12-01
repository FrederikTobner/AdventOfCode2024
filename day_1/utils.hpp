#pragma once

/**
 * @brief Checks if a character is considered whitespace
 * @param c Character to check
 * @return true if the character is whitespace, false otherwise
 * @note Whitespace characters include space, tab, newline and carriage return
 */
[[nodiscard]] constexpr auto isWhitespace(char c) noexcept -> bool {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}