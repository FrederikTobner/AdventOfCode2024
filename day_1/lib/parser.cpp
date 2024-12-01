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

namespace parser { // Add namespace wrapper

auto parseLine(std::string_view line) -> std::expected<std::pair<int64_t, int64_t>, std::error_code> {
    using enum std::errc;

    auto numbers = line | std::views::split(' ') |
                   std::views::filter([](auto && rng) { return !std::string_view(rng).empty(); }) |
                   std::views::transform([](auto && rng) -> std::expected<int64_t, std::error_code> {
                       try {
                           return std::stoll(std::string(rng.begin(), rng.end()));
                       } catch (...) {
                           return std::unexpected(std::make_error_code(invalid_argument));
                       }
                   });

    std::vector<std::expected<int64_t, std::error_code>> results = nonstd::ranges::to_vector(numbers);

    if (results.size() != 2 || !results[0] || !results[1]) {
        return std::unexpected(std::make_error_code(invalid_argument));
    }

    return std::pair{*results[0], *results[1]};
}

auto parseInput(std::string_view input)
    -> std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code> {

    std::vector<std::string_view> lines = nonstd::ranges::to_vector(
        input | std::views::split('\n') |
        std::views::transform([](auto && chars) { return std::string_view(chars.begin(), chars.end()); }) |
        std::views::filter([](auto sv) { return !isOnlyWhitespace(sv); }));

    std::multiset<int64_t> set1, set2;

    for (std::string_view const & line : lines) {
        std::expected<std::pair<int64_t, int64_t>, std::error_code> result = parseLine(line);
        if (!result) {
            return std::unexpected(result.error());
        }
        set1.insert(result->first);
        set2.insert(result->second);
    }

    return std::pair{set1, set2};
}

} // namespace parser