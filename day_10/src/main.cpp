#include <expected>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/trail_parser.hpp"
#include "../lib/trails.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::vector<std::string_view> lines = aoc::grid_processor::processLines(*input);
    if (!aoc::grid_processor::validateGrid(lines)) {
        std::println(stderr, "Lines have different lengths");
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto trails = aoc::day_10::convertToTrails(lines);

    // Part 1
    std::println("The number of unique paths is: {:#}", trails.calculateUniquePaths());

    // Part 2
    std::println("The total rating of all trails is: {:#}", trails.calculateRating());

    return 0;
}
