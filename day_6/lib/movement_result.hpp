#pragma once

namespace aoc::day_6 {

/// @brief Represents the possible outcomes of attempting to move the guard
enum class MovementResult {
    Moved,      ///< The guard successfully moved to a new position
    Blocked,    ///< The guard's movement was blocked by an obstacle
    OutOfBounds ///< The guard attempted to move outside the grid boundaries
};

} // namespace aoc::day_6