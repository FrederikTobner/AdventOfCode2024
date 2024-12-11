#include <execution>
#include <expected>
#include <ranges>
#include <string>
#include <system_error>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/parser.hpp"
#include "../lib/stone.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto numbers = aoc::day_11::parseNumbers(*input);

    if (!numbers) {
        std::println(stderr, "Error parsing input: {}", numbers.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    // Part 1
    std::println("Result after 25 iterations: {}", aoc::day_11::calculateStones(*numbers, 25));

    // Part 2
    std::println("Result after 75 iterations: {}", aoc::day_11::calculateStones(*numbers, 75));

    return 0;
}
