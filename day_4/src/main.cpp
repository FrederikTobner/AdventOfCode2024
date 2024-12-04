#include <algorithm>
#include <cstdint>
#include <ranges>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

#include "../lib/word_search.hpp"

int main(int argc, char const * argv[]) {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto lines = *input | std::views::split('\n') | std::views::transform([](auto && chars) {
        return std::string_view(chars.begin(), chars.end());
    }) | std::views::transform([](std::string_view sv) {
        if (sv.ends_with('\r')) {
            return sv.substr(0, sv.size() - 1);
        }
        return sv;
    }) | aoc::ranges::to<std::vector<std::string_view>>;

    if (std::ranges::any_of(lines, [&lines](auto const & line) { return line.size() != lines.front().size(); })) {
        std::println(stderr, "Lines have different lengths");
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto const grid = std::span{lines};
    auto matches = aoc::word_search::findWord(grid, "XMAS");

    std::println("Found {:#} XMAS matches:", matches.size());

    auto macthes2 = aoc::word_search::findWord(grid, "MAS");

    std::println("Found {:#} MAS matches:", macthes2.size());

    auto diagonal_matches = macthes2 | std::views::filter([](auto const & match) {
                                return match.coordinates[0].row != match.coordinates[1].row &&
                                       match.coordinates[0].col != match.coordinates[1].col;
                            }) |
                            aoc::ranges::to<std::vector<aoc::word_search::Match>>;

    std::println("Found {:#} diagonal MAS matches:", diagonal_matches.size());

    auto sum = std::ranges::count_if(diagonal_matches, [&diagonal_matches](auto const & match) {
        return std::ranges::any_of(diagonal_matches, [&match](auto const & other) {
            bool is_different_match = match.coordinates[0].row != other.coordinates[0].row ||
                                      match.coordinates[0].col != other.coordinates[0].col;
            bool has_same_second_pos = match.coordinates[1].row == other.coordinates[1].row &&
                                       match.coordinates[1].col == other.coordinates[1].col;
            return is_different_match && has_same_second_pos;
        });
    });
    std::println("Found {:#} matches with the same second position", sum);

    std::println("The result is {:#}", sum / 2);

    return 0;
}
