#pragma once

#include <algorithm>
#include <concepts>
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

/// @brief Parses a single puzzle from a string input
/// @tparam T The numeric type to use for puzzle results (defaults to size_t)
/// @param line String containing the puzzle in the format "result: value1 value2 ..."
/// @return Parsed equation puzzle
template <typename T = size_t>
    requires std::integral<T>
[[nodiscard]] auto parsePuzzle(std::string_view line) -> equation_puzzle<T>;

/// Parses puzzles from a string input into equation puzzles
/// @tparam T The numeric type to use for puzzle results (defaults to size_t)
/// @param input String containing puzzles in the format "result: value1 value2 ..."
/// @return Vector of parsed equation puzzles
/// Each puzzle line should be in the format: "target_number: value1 value2 value3 ..."
/// Lines are separated by newlines, values are separated by spaces
template <typename T = size_t>
    requires std::integral<T>
[[nodiscard]] auto parsePuzzles(std::string_view input)
    -> std::expected<std::vector<aoc::day_7::equation_puzzle<T>>, std::error_code>;

template <typename T>
    requires std::integral<T>
[[nodiscard]] auto parsePuzzles(std::string_view input)
    -> std::expected<std::vector<aoc::day_7::equation_puzzle<T>>, std::error_code> {
    try {
        return input | std::views::split('\n') | std::views::transform([](auto && line) {
                   if (line.back() == '\r') {
                       return std::string_view{line.begin(), line.end() - 1};
                   }
                   return std::string_view{line.begin(), line.end()};
               }) |
               std::views::filter([](auto && line) { return !line.empty(); }) |
               std::views::transform([](auto && line) { return parsePuzzle<T>(line); }) |
               aoc::ranges::to<std::vector<equation_puzzle<T>>>;
    } catch (...) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }
}

template <typename T>
    requires std::integral<T>
[[nodiscard]] auto parsePuzzle(std::string_view line) -> equation_puzzle<T> {
    auto colon_pos = line.find(':');
    std::expected<T, std::error_code> parsedExpectedResult =
        aoc::parser::rules::parse_number<T>(std::string(line.substr(0, colon_pos)));
    if (!parsedExpectedResult) {
        throw std::invalid_argument("Failed to parse number");
    }
    return equation_puzzle<T>{equation_result<T>{*parsedExpectedResult},
                              std::move(line.substr(colon_pos + 1) | std::views::split(' ') |
                                        std::views::transform([](auto && value) {
                                            return std::string_view{value.begin(), value.end()};
                                        }) |
                                        std::views::filter([](auto && value) { return !value.empty(); }) |
                                        std::views::transform([](auto && value) {
                                            std::expected<uint16_t, std::error_code> parsedValue =
                                                aoc::parser::rules::parse_number<uint16_t>(value);
                                            if (!parsedValue) {
                                                throw std::invalid_argument("Failed to parse number");
                                            }
                                            return *parsedValue;
                                        }) |
                                        aoc::ranges::to<std::vector<uint16_t>>)};
}

} // namespace aoc::day_7