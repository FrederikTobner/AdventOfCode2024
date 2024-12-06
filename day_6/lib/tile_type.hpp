#pragma once

namespace aoc::day_6 {

/// @brief Represents the different types of tiles that can exist in the puzzle grid
enum class TileType {
    Empty,   ///< An empty space (represented as '.' in the input)
    Guard,   ///< The guard's position (represented as '^', 'v', '<', '>' in the input)
    Obstacle ///< An impassable obstacle (represented as '#' in the input)
};

} // namespace aoc::day_6