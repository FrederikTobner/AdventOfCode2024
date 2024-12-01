#pragma once

// GCC and Clang have not yet implemented the print library, so we need to use the format library instead
#if defined(__GNUC__) && !defined(__clang__)
#include <format>
#include <iostream>

namespace std {
template <typename... Args> void println(std::format_string<Args...> fmt, Args &&... args) {
    std::cout << std::vformat(fmt.get(), std::make_format_args(args...)) << '\n';
}

template <typename... Args> void println(std::FILE * stream, std::format_string<Args...> fmt, Args &&... args) {
    std::fprintf(stream, "%s\n", std::vformat(fmt.get(), std::make_format_args(args...)).c_str());
}
} // namespace std
#else // MSVC already has the print library implemented
#include <print>
#endif