#pragma once

#include <array>
#include <cstdint>
#include <ranges>
#include <stdexcept>
#include <vector>

#include "topography.hpp"
#include "trails.hpp"

#include "../../shared/src/vector3d.hpp"

namespace aoc::day_10 {

/// Represents the four possible directions of movement on the trail
enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

/// Calculates a new position based on the current position and direction of movement
/// @param current The current position in the grid
/// @param dir The direction to move in
/// @return The new position after moving in the specified direction
/// @throws std::invalid_argument if an invalid direction is provided
static inline auto calculateNewPosition(aoc::math::vector_3d<uint8_t> const & current, Direction dir)
    -> aoc::math::vector_2d<uint8_t> {
    switch (dir) {
    case Direction::UP:
        return {static_cast<uint8_t>(current.x - 1), current.y};
    case Direction::RIGHT:
        return {current.x, static_cast<uint8_t>(current.y + 1)};
    case Direction::DOWN:
        return {static_cast<uint8_t>(current.x + 1), current.y};
    case Direction::LEFT:
        return {current.x, static_cast<uint8_t>(current.y - 1)};
    }
    throw std::invalid_argument("Invalid direction");
}

/// Checks if a given position is within the bounds of the map
/// @param pos The position to check
/// @param map The 2D map representing the trail system
/// @return true if the position is valid, false otherwise
static inline auto isValidPosition(aoc::math::vector_2d<uint8_t> const & pos,
                                   std::vector<std::vector<uint8_t>> const & map) -> bool {
    return pos.x < map.size() && pos.y < map[0].size();
}

/// Creates a new tree node for the trail system
/// @param pos The position of the node in the grid
/// @param value The value at this position
/// @param children The child nodes connected to this position
/// @return A new tree node representing this position in the trail
static inline auto createNode(aoc::math::vector_3d<uint8_t> const & pos,
                              std::vector<aoc::tree::tree_node<aoc::math::vector_3d<uint8_t>>> children)
    -> aoc::tree::tree_node<aoc::math::vector_3d<uint8_t>> {
    return {pos, std::move(children)};
}

/// Determines the valid child nodes for a given position in the map
/// @param map The 2D map representing the trail system
/// @param pos The current position to find children for
/// @return A vector of tree nodes representing valid next positions
static auto determineChildren(std::vector<std::vector<uint8_t>> const & map, aoc::math::vector_3d<uint8_t> const & pos)
    -> std::vector<aoc::tree::tree_node<aoc::math::vector_3d<uint8_t>>>;

/// Converts a 2D map into a trail system representation
/// @param map The 2D map containing trail values (0-9)
/// @return A trails object containing the complete trail system
auto convertToTrails(std::vector<std::vector<uint8_t>> const & map) -> trails;

} // namespace aoc::day_10