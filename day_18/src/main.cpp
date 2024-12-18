#include <expected>
#include <string>
#include <system_error>

#include "../../shared/src/astar.hpp"
#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/vector2d.hpp"

#include "../lib/blocker.hpp"
#include "../lib/maze.hpp"
#include "../lib/parser.hpp"

auto main(int argc, char const ** argv) -> int {
    auto parsed_numbers = aoc::day_18::parseInput("input.txt");
    if (!parsed_numbers) {
        std::println(stderr, "Could not open file: {}", parsed_numbers.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto base_maze = aoc::day_18::buildMaze(*parsed_numbers, 1024);

    // Part 1
    auto shortest_route = aoc::path_finding::MazeSolver(base_maze.m_maze, aoc::day_18::scoringFun).findPath();
    std::println("Shortest path cost for initial maze: {}", shortest_route.cost);

    // Part 2
    auto [critical_x, critical_y] = aoc::day_18::findCriticalWall(*parsed_numbers);
    if (critical_x != -1) {
        std::println("Critical wall found at {},{}", critical_x, critical_y);
    }

    return 0;
}
