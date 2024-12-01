/**
 * @file parser.cpp
 * @brief Implementation of input parsing functionality
 * @details Contains the implementation of parsing functions declared in parser.hpp.
 * Handles the conversion of string input into numerical data structures with
 * proper error handling.
 */

#include "parser.hpp"
#include "../../shared/ranges_compatibility_layer.hpp"

#include <algorithm>
#include <ranges>
#include <string>
#include <vector>

constexpr auto isOnlyWhitespace(std::string_view str) -> bool {
    return str.empty() || std::ranges::all_of(str, isWhitespace);
}

auto parseLine(std::string_view line) -> std::expected<std::pair<int64_t, int64_t>, std::error_code> {
    try {
        auto numbers = compat::to_vector(
            line | std::views::split(' ') |
            std::views::filter([](auto && rng) { return !std::string_view(rng).empty(); }) |
            std::views::transform([](auto && rng) { return std::stoll(std::string(rng.begin(), rng.end())); }));

        if (numbers.size() != 2) {
            return std::unexpected(std::make_error_code(std::errc::invalid_argument));
        }

        return std::pair{numbers[0], numbers[1]};
    } catch (...) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }
}

auto parseInput(std::string_view input)
    -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code> {

    auto lines = compat::to_vector(input | std::views::split('\n') | std::views::transform([](auto && chars) {
                                       return std::string_view(chars.begin(), chars.end());
                                   }) |
                                   std::views::filter([](auto sv) { return !isOnlyWhitespace(sv); }));

    std::multiset<int64_t> set1, set2;

    for (std::string_view const & line : lines) {
        auto result = parseLine(line);
        if (!result) {
            return std::unexpected(result.error());
        }
        set1.insert(result->first);
        set2.insert(result->second);
    }

    return std::pair{set1, set2};
}