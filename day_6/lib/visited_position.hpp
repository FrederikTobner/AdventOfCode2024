#pragma once

#include "facing_direction.hpp"

namespace aoc::day_6 {

struct VisitedPosition {
    size_t row;
    size_t col;
    FacingDirection direction;

    // Spaceship operator
    auto operator<=>(VisitedPosition const &) const = default;
};
} // namespace aoc::day_6

namespace std {

/// @brief Hashes the given VisitedPosition.
template <> struct hash<aoc::day_6::VisitedPosition> {

    /// @brief Hashes the given VisitedPosition.
    /// @param position The VisitedPosition to hash.
    /// @return The hash of the given position.
    [[nodiscard]] auto operator()(aoc::day_6::VisitedPosition const position) const -> std::size_t {
        return std::hash<size_t>{}(position.row) ^ std::hash<size_t>{}(position.col) ^
               std::hash<aoc::day_6::FacingDirection>{}(position.direction);
    }
};
} // namespace std