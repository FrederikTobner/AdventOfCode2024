#pragma once

#include "facing_direction.hpp"

#include <memory> // for std::hash

namespace aoc::day_6 {

/// @brief Represents a position that has been visited by the guard
/// @details Stores both the coordinates and the direction the guard was facing
///          Used to detect loops in the guard's movement pattern
struct VisitedPosition {
    /// @brief The row coordinate in the grid
    size_t row;
    /// @brief The column coordinate in the grid
    size_t col;
    /// @brief The direction the guard was facing at this position
    FacingDirection direction;

    /// @brief Equality operator for comparing VisitedPositions
    /// @param other The other VisitedPosition to compare against
    /// @return True if the positions are equal, false otherwise
    [[nodiscard]] auto operator==(VisitedPosition const & other) const -> bool {
        return row == other.row && col == other.col && direction == other.direction;
    }
};

} // namespace aoc::day_6

namespace std {

/// @brief Hash specialization for VisitedPosition to enable use in unordered containers
template <> struct hash<aoc::day_6::VisitedPosition> {
    /// @brief Combines the hashes of row, column and direction into a single hash value
    /// @param position The position to hash
    /// @return A hash value representing the complete state of the position
    [[nodiscard]] auto operator()(aoc::day_6::VisitedPosition const position) const -> std::size_t {
        return std::hash<size_t>{}(position.row) ^ std::hash<size_t>{}(position.col) ^
               std::hash<aoc::day_6::FacingDirection>{}(position.direction);
    }
};
} // namespace std
