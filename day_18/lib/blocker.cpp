#include "blocker.hpp"

#include <algorithm>
#include <ranges>

namespace aoc::day_18 {

auto scoringFun(aoc::path_finding::Node const & a, aoc::path_finding::Node const & b) -> int {
    return 1;
}

auto validatePath(maze const & maze, auto const & scoringFun) -> bool {
    auto shortest_route = aoc::path_finding::MazeSolver(maze.m_maze, scoringFun).findPath();
    return shortest_route.cost == -1;
}

auto findCriticalWall(std::vector<std::vector<int16_t>> const & coordinates, size_t min)
    -> std::pair<int16_t, int16_t> {
    for (auto i : std::views::iota(min, coordinates.size()) | std::views::reverse) {
        auto test_maze = buildMaze(coordinates, i);
        if (!validatePath(test_maze, scoringFun)) {
            return {coordinates[i][0], coordinates[i][1]};
        }
    }
    return {-1, -1};
}
} // namespace aoc::day_18