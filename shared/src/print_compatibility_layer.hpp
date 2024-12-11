/**
 * @file print_compatibility_layer.hpp
 * @brief Compatibility layer for std::print functionality
 * @details Provides cross-compiler compatibility for C++23 print features,
 * implementing fallbacks for compilers that don't yet support the print library.
 * Specifically handles GCC and Clang differently from MSVC.
 */

#pragma once

// GCC has not yet implemented the print library, so we need to use the format library instead and implement the print
// functions ourselves
#if defined(__GNUC__) && !defined(__clang__)
#include <format>
#include <iostream>

namespace std {

/// @brief Prints a formatted string to the standard output stream
/// @tparam ...Args Types of the arguments to format
/// @param fmt Format string
/// @param ...args Arguments to format
template <typename... Args> void print(std::format_string<Args...> fmt, Args &&... args) {
    std::cout << std::vformat(fmt.get(), std::make_format_args(args...));
}

/// @brief Prints a formatted string to the specified output stream
/// @tparam ...Args Types of the arguments to format
/// @param stream Output stream to write to
/// @param fmt Format string
/// @param ...args Arguments to format
template <typename... Args> void print(std::FILE * stream, std::format_string<Args...> fmt, Args &&... args) {
    std::fprintf(stream, "%s", std::vformat(fmt.get(), std::make_format_args(args...)).c_str());
}

/// @brief Prints a formatted string to the standard output stream
/// @tparam ...Args Types of the arguments to format
/// @param fmt Format string
/// @param ...args Arguments to format
template <typename... Args> void println(std::format_string<Args...> fmt, Args &&... args) {
    std::cout << std::vformat(fmt.get(), std::make_format_args(args...)) << '\n';
}

/// @brief Prints a formatted string to the specified output stream
/// @tparam ...Args Types of the arguments to format
/// @param stream Output stream to write to
/// @param fmt Format string
/// @param ...args Arguments to format
template <typename... Args> void println(std::FILE * stream, std::format_string<Args...> fmt, Args &&... args) {
    std::fprintf(stream, "%s\n", std::vformat(fmt.get(), std::make_format_args(args...)).c_str());
}

} // namespace std
#else // MSVC and Clang already have the print library implemented - nothing to do here
#include <print>
#endif