#pragma once

// GCC 13 and clang do not have the <print> header yet, so we need to use the <format> header and define our own println
// function. This function will be used to print formatted strings to the console or a file.
#if defined(__GNUC__) && !defined(__clang__)
#include <format>
#include <iostream>

namespace std {
template <typename... Args> void println(const std::string_view fmt, Args &&... args) {
    std::cout << std::format(fmt, std::forward<Args>(args)...) << '\n';
}

template <typename... Args> void println(std::FILE * stream, const std::string_view fmt, Args &&... args) {
    std::fprintf(stream, "%s\n", std::format(fmt, std::forward<Args>(args)...).c_str());
}
} // namespace std
#else // MSVC already supports the <print> header
#include <print>
#endif