#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "maze.hpp"

#include "../../shared/src/astar.hpp"

namespace aoc::day_18 {

/// @brief Scoring function for A* pathfinding
/// @param a First node
/// @param b Second node
/// @return Cost between nodes
auto scoringFun(aoc::path_finding::Node const & a, aoc::path_finding::Node const & b) -> int;

/// @brief Validates if a path exists through the maze
/// @param maze The maze to validate
/// @param scoringFun Function used to score path segments
/// @return True if no path exists, false otherwise
auto validatePath(maze const & maze, auto const & scoringFun) -> bool;

/// @brief Finds the critical wall that blocks all paths
/// @param coordinates Vector of coordinate pairs
/// @param min Minimum index to start searching from
/// @return Pair of coordinates for the critical wall, or {-1,-1} if none found
auto findCriticalWall(std::vector<std::vector<int16_t>> const & coordinates, size_t min = 1025ull)
    -> std::pair<int16_t, int16_t>;
} // namespace aoc::day_18