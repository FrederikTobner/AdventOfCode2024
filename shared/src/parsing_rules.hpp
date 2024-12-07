#pragma once

#include <charconv>
#include <concepts>
#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>

namespace aoc::parser::rules {

namespace detail {
template <typename T> auto parse_unsigned(std::string_view token) -> std::expected<T, std::error_code> {
    T value;
    auto [ptr, errorCode] = std::from_chars(token.data(), token.data() + token.size(), value);
    if (errorCode != std::errc()) {
        return std::unexpected(std::make_error_code(errorCode));
    }
    return value;
}

template <typename T> auto parse_signed(std::string_view token) -> std::expected<T, std::error_code> {
    try {
        if constexpr (std::is_integral_v<T>) {
            return static_cast<T>(std::stoll(std::string(token)));
        } else {
            return static_cast<T>(std::stold(std::string(token)));
        }
    } catch (...) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }
}
} // namespace detail

template <typename T>
    requires std::is_arithmetic_v<T>
auto parse_number(std::string_view token) -> std::expected<T, std::error_code> {
    if constexpr (std::is_unsigned_v<T>) {
        return detail::parse_unsigned<T>(token);
    } else {
        return detail::parse_signed<T>(token);
    }
}

} // namespace aoc::parser::rules