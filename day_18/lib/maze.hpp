#pragma once

#include <ranges>
#include <string>
#include <vector>

#include "../../shared/src/maze_cell.hpp"

namespace aoc::day_18 {

#define DIMENSIONS 71

/// @brief Represents a 2D maze with start and end points
struct maze {
    /// @brief Constructs an empty maze with start and end points
    maze();

    /// @brief Converts the maze to a string representation
    /// @return String representation of the maze
    std ::string to_string();

    /// @brief The actual maze data
    std::vector<std::vector<aoc::path_finding::maze_cell>> m_maze;
};

/// @brief Builds a maze from coordinate pairs
/// @param coordinates Vector of coordinate pairs
/// @param limit Maximum number of coordinates to use
/// @return Constructed maze
auto buildMaze(std::vector<std::vector<int16_t>> const & coordinates, size_t limit) -> maze;

} // namespace aoc::day_18