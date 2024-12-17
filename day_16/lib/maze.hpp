#pragma once

#include <string_view>
#include <vector>

#include "maze_cell.hpp"

namespace aoc::day_16 {

/// @brief Parses the maze from the input
/// @param lines The input to parse
/// @return The parsed maze
auto parseMaze(std::vector<std::string_view> lines) -> std::vector<std::vector<maze_cell>>;

} // namespace aoc::day_16