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

// Concept for types that can be parsed from string
template <typename T>
concept IsNumber = std::is_arithmetic_v<T>;

namespace detail {
template <typename T> auto parse_unsigned(std::string_view token) -> std::expected<T, std::error_code> {
    T value;
    auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), value);
    if (ec != std::errc()) {
        return std::unexpected(std::make_error_code(ec));
    }
    return value;
}

template <typename T> auto parse_signed(std::string_view token) -> std::expected<T, std::error_code> {
    try {
        if constexpr (sizeof(T) <= sizeof(long long)) {
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
    requires IsNumber<T>
auto parse_number(std::string_view token) -> std::expected<T, std::error_code> {
    if constexpr (std::is_unsigned_v<T>) {
        return detail::parse_unsigned<T>(token);
    } else {
        return detail::parse_signed<T>(token);
    }
}

} // namespace aoc::parser::rules