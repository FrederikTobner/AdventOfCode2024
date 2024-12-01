#include "parser.hpp"
#include "utils.hpp"
#include <ranges>
#include <string>
#include <algorithm>

auto isOnlyWhitespace(std::string_view str) -> bool {
    return str.empty() || 
           std::ranges::all_of(str, [](char c) { return isWhitespace(c); });
}

auto parseLine(std::string_view line) -> std::pair<int64_t, int64_t> {
    auto numbers = line | std::views::split(' ') |
                   std::views::filter([](auto && rng) { return !std::string_view(rng).empty(); }) |
                   std::views::transform([](auto && rng) { return std::stoll(std::string(rng.begin(), rng.end())); });

    auto iterator = numbers.begin();
    return {*iterator++, *iterator};
}

auto parseInput(std::string_view input) -> std::pair<std::multiset<int64_t>, std::multiset<int64_t>> {
    std::multiset<int64_t> set1, set2;

    auto lines = input | std::views::split('\n') |
                 std::views::transform([](auto && chars) { return std::string_view(chars.begin(), chars.end()); }) |
                 std::views::filter([](auto stringView) { return !isOnlyWhitespace(stringView); });

    for (std::string_view const & line : lines) {
        auto [a, b] = parseLine(line);
        set1.insert(a);
        set2.insert(b);
    }

    return {set1, set2};
}