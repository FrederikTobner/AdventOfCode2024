#pragma once

#include <algorithm>
#include <cstdint>
#include <ranges>
#include <vector>

#include "../../shared/src/astar.hpp"
#include "maze.hpp"

namespace aoc::day_18 {
static auto validatePath(maze const & maze, auto const & scoringFun) -> bool {
    auto shortest_route = aoc::path_finding::MazeSolver(maze.m_maze, scoringFun).findPath();
    return shortest_route.cost == -1;
}

auto findCriticalWall(std::vector<std::vector<int16_t>> const & coordinates) -> std::pair<int16_t, int16_t> {
    for (auto i : std::views::iota(1025ull, coordinates.size()) | std::views::reverse) {
        auto test_maze = buildMaze(coordinates, i);
        if (!validatePath(test_maze, scoringFun)) {
            return {coordinates[i][0], coordinates[i][1]};
        }
    }
    return {-1, -1};
}
} // namespace aoc::day_18