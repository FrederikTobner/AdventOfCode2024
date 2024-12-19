#include <execution>
#include <expected>
#include <numeric>
#include <string>
#include <system_error>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/matcher.hpp"
#include "../lib/parser.hpp"

struct pattern_matching_result {
    size_t solvable;
    size_t solutions;

    pattern_matching_result operator+(pattern_matching_result const & other) const {
        return {solvable + other.solvable, solutions + other.solutions};
    }
};

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::expected<aoc::day_19::puzzle_input, std::error_code> parsed_input = aoc::day_19::parseInput(*input);
    if (!parsed_input) [[unlikely]] {
        std::println(stderr, "Could not parse input: {}", parsed_input.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto matcher = aoc::day_19::pattern_matcher(parsed_input->patterns);
    auto counts =
        std::transform_reduce(std::execution::seq, parsed_input->designs.begin(), parsed_input->designs.end(),
                              pattern_matching_result{0, 0}, std::plus<>(), [&matcher](auto const & design) {
                                  if (matcher.can_construct(design)) {
                                      return pattern_matching_result{1, matcher.count_unique_ways_to_construct(design)};
                                  }
                                  return pattern_matching_result{0, 0};
                              });

    // Part 1
    std::println("Solvable designs: {}", counts.solvable);

    // Part 2
    std::println("Total solutions count: {}", counts.solutions);

    return 0;
}
