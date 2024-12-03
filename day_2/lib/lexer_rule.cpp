#include "lexer_rule.hpp"

#include <algorithm>
#include <charconv>
#include <ranges>

#include "../../shared/ranges_compatibility_layer.hpp"

auto aoc::lexer::rules::handleToken(std::string_view token) -> std::expected<uint8_t, std::error_code> {
    uint8_t value;
    auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), value);
    if (ec != std::errc()) {
        return std::unexpected(std::make_error_code(ec));
    }
    return value;
}