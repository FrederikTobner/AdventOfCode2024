#pragma once

#include <algorithm>
#include <expected>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "equation_puzzle.hpp"

namespace aoc::day_7 {
auto parsePuzzles(std::string_view input) -> std::vector<aoc::day_7::equation_puzzle> {
    auto puzzle_input =
        input | std::views::split('\n') | std::views::transform([](auto && line) {
            if (line.back() == '\r') {
                return std::string_view{line.begin(), line.end() - 1};
            }
            return std::string_view{line.begin(), line.end()};
        }) |
        std::views::filter([](auto && line) { return !line.empty(); }) | std::views::transform([](auto && line) {
            auto colon_pos = line.find(':');
            auto result = aoc::day_7::equation_result<>{std::stoull(std::string(line.substr(0, colon_pos)))};
            auto values_range = line.substr(colon_pos + 1);
            std::string values_str(values_range.begin(), values_range.end());
            return std::pair{result, values_str};
        });

    std::vector<aoc::day_7::equation_puzzle> puzzles;
    for (auto && [expected_result, values] : puzzle_input) {
        aoc::day_7::equation_puzzle eq{expected_result, {}};
        auto values_split = values | std::views::split(' ') | std::views::transform([](auto && value) {
                                return std::string_view{value.begin(), value.end()};
                            }) |
                            std::views::filter([](auto && value) { return !value.empty(); }) |
                            aoc::ranges::to<std::vector<std::string_view>>;
        for (auto && value : values_split) {
            eq.values.push_back(std::stoul(std::string(value)));
        }
        puzzles.push_back(std::move(eq));
    }
    return puzzles;
}

} // namespace aoc::day_7