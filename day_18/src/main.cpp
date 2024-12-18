#include <cmath>
#include <cstdint>
#include <execution>
#include <expected>
#include <string>
#include <system_error>
#include <unordered_set>

#include "../../shared/src/astar.hpp"
#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/line_splitter.hpp"
#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/vector2d.hpp"

#include "../lib/maze.hpp"

auto main(int argc, char const ** argv) -> int {

    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto parsed_numbers = aoc::splitter::linebased::split<int16_t, std::vector>(
        *input, aoc::parser::rules::parse_number<int16_t>, std::execution::seq, ',');

    auto maze = aoc::day_18::maze{};
    size_t counter = 0;
    for (auto const & line : *parsed_numbers) {
        if (counter == 1024) {
            break;
        }
        maze.m_maze[(line[0] + 1)][(DIMENSIONS + 1) - (line[1] + 1)] = aoc::path_finding::maze_cell::WALL;
        counter++;
    }

    std::println("Maze:\n{}", maze.to_string());

    auto scoringFun = [](aoc::path_finding::Node const & a, aoc::path_finding::Node const & b) { return 1; };

    auto shortest_route = aoc::path_finding::MazeSolver(maze.m_maze, scoringFun).findPath();

    auto unique_nodes = std::unordered_set<aoc::math::vector_2d<int16_t>>{};

    for (auto const & node : shortest_route.path) {
        unique_nodes.insert(node.pos);
    }

    std::println("Shortest path cost: {}", unique_nodes.size() - 1);

    return 0;
}
