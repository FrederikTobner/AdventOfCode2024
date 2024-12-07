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
#include "../lib/equation_puzzle_parser.hpp"
#include "../lib/equation_puzzle_solver.hpp"
#include "../lib/equation_result.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto calculate_sum = [](std::span<aoc::day_7::operator_desc const * const> ops) {
        return [ops](auto const & puzzle) { return aoc::day_7::isSolvable(puzzle, ops) ? puzzle.result.raw() : 0; };
    };

    std::vector<aoc::day_7::equation_puzzle> puzzles = aoc::day_7::parsePuzzles(*input);

    size_t part_1_sum = aoc::ranges::fold_left(
        puzzles | std::views::transform(calculate_sum(std::span(aoc::day_7::BASIC_OPERATORS))), size_t{0}, std::plus{});
    std::println("Sum of all results: {} using basic operators", part_1_sum);

    size_t part_2_sum = aoc::ranges::fold_left(
        puzzles | std::views::transform(calculate_sum(std::span(aoc::day_7::ALL_OPERATORS))), size_t{0}, std::plus{});
    std::println("Sum of all results: {} using all operators", part_2_sum);
    return 0;
}
