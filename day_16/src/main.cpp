#include <expected>
#include <ranges>
#include <string>
#include <system_error>
#include <unordered_set>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/astar.hpp"
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

    auto maze = aoc::day_16::parseMaze(grid);

    // Part 1

    auto shortest_route = aoc::day_16::MazeSolver(maze).findPath();

    if (shortest_route.cost == -1) {
        std::println("No path found");
    } else {
        std::println("Shortest path cost: {}", shortest_route.cost);
    }

    // Part 2

    auto shortest_routes = aoc::day_16::MazeSolver(maze).findPaths();

    std::println("Found {} paths", shortest_routes.size());

    std::unordered_set<aoc::math::vector_2d<int16_t>> visited;

    for (auto const & path : shortest_routes) {
        for (auto const & node : path.path) {
            visited.insert(node.pos);
        }
    }

    std::println("Visited {} nodes", visited.size());

    return aoc::EXIT_CODE_SUCCESS;
}
