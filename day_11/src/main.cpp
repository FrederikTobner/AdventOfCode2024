#include <execution>
#include <expected>
#include <ranges>
#include <string>
#include <system_error>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/line_splitter.hpp"
#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/stone.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto parsed_numbers =
        aoc::splitter::linebased::split<size_t, std::vector>(*input, aoc::parser::rules::parse_number<size_t>, ' ');

    if (!parsed_numbers) {
        std::println(stderr, "Error parsing input: {}", parsed_numbers.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }
    if (parsed_numbers->empty()) {
        std::println(stderr, "No numbers found in input");
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto numbers = (*parsed_numbers)[0];

    // Part 1
    std::println("Result after 25 iterations: {}", aoc::day_11::calculateStones(numbers, 25, std::execution::seq));

    // Part 2
    std::println("Result after 75 iterations: {}", aoc::day_11::calculateStones(numbers, 75, std::execution::seq));

    return 0;
}
