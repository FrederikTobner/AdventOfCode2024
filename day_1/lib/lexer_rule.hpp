#pragma once

#include <cstdint>
#include <expected>
#include <string>
#include <string_view>
#include <system_error>

namespace aoc::lexer::rules {

std::expected<int64_t, std::error_code> numberProducer(std::string_view sv) {
    try {
        return std::stoll(std::string(sv));
    } catch (...) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }
}
} // namespace aoc::lexer::rules