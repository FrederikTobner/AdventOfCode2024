#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

#include <algorithm>
#include <expected>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "../lib/equation_puzzle.hpp"
#include "../lib/equation_puzzle_solver.hpp"
#include "../lib/equation_result.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }
    // Split the input into lines
    auto lines = *input | std::views::split('\n') | std::views::transform([](auto && line) {
        if (line.back() == '\r') {
            return std::string_view{line.begin(), line.end() - 1};
        }
        return std::string_view{line.begin(), line.end()};
    }) | std::views::filter([](auto && line) { return !line.empty(); });
    // Split the lines by :
    auto split_lines = lines | std::views::transform([](auto && line) {
                           auto colon_pos = line.find(':');
                           auto result =
                               aoc::day_7::equation_result<>{std::stoull(std::string(line.substr(0, colon_pos)))};

                           // Create proper string from range
                           auto values_range = line.substr(colon_pos + 1);
                           std::string values_str(values_range.begin(), values_range.end());
                           return std::pair{result, values_str};
                       });

    size_t part_1_sum = 0;
    for (auto && [expected_result, values] : split_lines) {
        aoc::day_7::equation_puzzle eq{expected_result, {}};
        // Split the values by spaces
        auto values_split = values | std::views::split(' ') | std::views::transform([](auto && value) {
                                return std::string_view{value.begin(), value.end()};
                            }) |
                            std::views::filter([](auto && value) { return !value.empty(); }) |
                            aoc::ranges::to<std::vector<std::string_view>>;
        for (auto && value : values_split) {
            eq.values.push_back(std::stoul(std::string(value)));
        }
        if (aoc::day_7::isSolvable(eq, std::span(aoc::day_7::BASIC_OPERATORS))) {
            part_1_sum += expected_result.raw();
        }
    }
    std::println("Sum of all results: {} using basic operators", part_1_sum);
    size_t part_2_sum = 0;
    for (auto && [expected_result, values] : split_lines) {
        aoc::day_7::equation_puzzle eq{expected_result, {}};
        // Split the values by spaces
        auto values_split = values | std::views::split(' ') | std::views::transform([](auto && value) {
                                return std::string_view{value.begin(), value.end()};
                            }) |
                            std::views::filter([](auto && value) { return !value.empty(); }) |
                            aoc::ranges::to<std::vector<std::string_view>>;
        for (auto && value : values_split) {
            eq.values.push_back(std::stoul(std::string(value)));
        }
        if (aoc::day_7::isSolvable(eq, std::span(aoc::day_7::ALL_OPERATORS))) {
            part_2_sum += expected_result.raw();
        }
    }
    std::println("Sum of all results: {} using all operators", part_2_sum);
    return 0;
}
