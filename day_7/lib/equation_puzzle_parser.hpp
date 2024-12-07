#pragma once

#include <algorithm>
#include <expected>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"
#include "equation_puzzle.hpp"

namespace aoc::day_7 {

/// Parses puzzles from a string input into equation puzzles
/// @tparam T The numeric type to use for puzzle results (defaults to size_t)
/// @param input String containing puzzles in the format "result: value1 value2 ..."
/// @return Vector of parsed equation puzzles
/// Each puzzle line should be in the format: "target_number: value1 value2 value3 ..."
/// Lines are separated by newlines, values are separated by spaces
template <typename T = size_t>
auto parsePuzzles(std::string_view input) -> std::vector<aoc::day_7::equation_puzzle<T>> {
    return input | std::views::split('\n') | std::views::transform([](auto && line) {
               if (line.back() == '\r') {
                   return std::string_view{line.begin(), line.end() - 1};
               }
               return std::string_view{line.begin(), line.end()};
           }) |
           std::views::filter([](auto && line) { return !line.empty(); }) | std::views::transform([](auto && line) {
               auto colon_pos = line.find(':');
               auto numberParser = aoc::parser::rules::parse_number<T>(std::string(line.substr(0, colon_pos)));
               auto result = aoc::day_7::equation_result<T>{*numberParser};
               auto values_range = line.substr(colon_pos + 1);

               auto values = values_range | std::views::split(' ') | std::views::transform([](auto && value) {
                                 return std::string_view{value.begin(), value.end()};
                             }) |
                             std::views::filter([](auto && value) { return !value.empty(); }) |
                             std::views::transform(
                                 [](auto && value) { return static_cast<uint16_t>(std::stoul(std::string(value))); }) |
                             aoc::ranges::to<std::vector<uint16_t>>;

               return equation_puzzle<T>{result, std::move(values)};
           }) |
           aoc::ranges::to<std::vector<equation_puzzle<T>>>;
}

} // namespace aoc::day_7