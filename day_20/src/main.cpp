#include <expected>
#include <ranges>
#include <string>
#include <system_error>
#include <unordered_set>
#include <vector>

#include "../../shared/src/astar.hpp"
#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/maze.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto grid = aoc::grid_processor::processLines(*input);

    if (!aoc::grid_processor::validateGrid(grid)) {
        std::println(stderr, "Grid is not valid");
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto maze = aoc::day_20::parseMaze(grid);

    auto scoringFun = [](aoc::path_finding::Node const & a, aoc::path_finding::Node const & b) { return 1; };

    // Part 1
    auto possible_cheats = aoc::path_finding::MazeSolver(maze, scoringFun).findPathUsingCheats(2);

    // Sort by saving
    std::ranges::sort(possible_cheats, [](auto const & a, auto const & b) { return a.saving > b.saving; });

    for (size_t i = 0; i < possible_cheats.size(); i++) {
        if (possible_cheats[i].saving < 100) {
            std::println("Found paths with a saving over 100: {}", i);
            break;
        }
    }

    return aoc::EXIT_CODE_SUCCESS;
}
