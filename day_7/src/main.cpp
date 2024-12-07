#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

#include <algorithm>
#include <expected>
#include <ranges>
#include <span>
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

    auto basic_ops = std::span<aoc::day_7::equation_operator_t<> const * const, aoc::day_7::BASIC_OPERATORS_SIZE<>>{
        aoc::day_7::BASIC_OPERATORS_T<>.data(), std::size(aoc::day_7::BASIC_OPERATORS_T<>)};

    auto all_ops = std::span<aoc::day_7::equation_operator_t<> const * const, aoc::day_7::ALL_OPERATORS_SIZE<>>{
        aoc::day_7::ALL_OPERATORS_T<>.data(), std::size(aoc::day_7::ALL_OPERATORS_T<>)};

    auto calculate_sum = [](auto ops) {
        return [ops](auto const & puzzle) {
            return aoc::day_7::isSolvable<size_t>(puzzle, ops) ? puzzle.result.raw() : 0;
        };
    };

    std::vector<aoc::day_7::equation_puzzle<>> puzzles = aoc::day_7::parsePuzzles<>(*input);

    size_t part_1_sum =
        aoc::ranges::fold_left(puzzles | std::views::transform(calculate_sum(basic_ops)), size_t{0}, std::plus{});

    size_t part_2_sum =
        aoc::ranges::fold_left(puzzles | std::views::transform(calculate_sum(all_ops)), size_t{0}, std::plus{});

    std::println("Sum of all results: {} using basic operators", part_1_sum);
    std::println("Sum of all results: {} using all operators", part_2_sum);
    return 0;
}
