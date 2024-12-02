#include "parser.hpp"
#include "../../shared/ranges_compatibility_layer.hpp"
#include <algorithm>
#include <charconv>
#include <ranges>

auto parser::parseInput(std::string_view input) -> std::expected<std::vector<std::vector<uint8_t>>, std::error_code> {
    std::vector<std::vector<uint8_t>> result;

    auto lines = input | std::views::split('\n') |
                 std::views::transform([](auto && chars) { return std::string_view(chars.begin(), chars.end()); }) |
                 std::views::filter([](std::string_view sv) { return !isOnlyWhitespace(sv); });

    for (std::string_view const & line : lines) {
        auto parsed = parseLine(line);
        if (!parsed) {
            return std::unexpected(parsed.error());
        }
        result.push_back(*parsed);
    }

    return result;
}

auto parser::parseLine(std::string_view line) -> std::expected<std::vector<uint8_t>, std::error_code> {
    std::vector<uint8_t> result;

    auto tokens = line | std::views::split(' ') |
                  std::views::transform([](auto && chars) { return std::string_view(chars.begin(), chars.end()); }) |
                  std::views::filter([](std::string_view sv) { return !isOnlyWhitespace(sv); });

    for (std::string_view token : tokens) {
        uint8_t value;
        auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), value);

        if (ec != std::errc()) {
            return std::unexpected(std::make_error_code(ec));
        }
        result.push_back(value);
    }

    return result;
}