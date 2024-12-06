#pragma once

#include <format>
#include <span>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

#include "facing_direction.hpp"
#include "movement_result.hpp"
#include "tile_type.hpp"
#include "visited_position.hpp"

namespace aoc::day_6 {

/// @brief A Map representing a 2D grid with a guard that can move and interact with obstacles
///
/// The guard moves according to these rules:
/// - If there are no obstacles ahead, move forward in the current direction
/// - If blocked by an obstacle, turn right
/// - If reaching map bounds, stop moving
class PuzzleMap {
  public:
    /// @brief Constructs a new puzzle map with a guard at a specific position and direction
    /// @param grid The 2D grid of tiles representing the map
    /// @param startPosition The initial position of the guard as {row, col}
    /// @param startDirection The initial direction the guard is facing
    PuzzleMap(std::vector<std::vector<TileType>> grid, std::pair<int64_t, int64_t> startPosition,
              FacingDirection startDirection);

    /// @brief Converts the current map state to a string representation
    /// @return A string showing the map with '.' for empty, '#' for obstacles, and '^v<>' for the guard
    [[nodiscard]] auto toString() const -> std::string;

    /// @brief Updates the guard's position and direction according to movement rules
    /// @return false if a loop is detected, true otherwise
    bool update();

    /// @brief Checks if the guard has moved outside the map boundaries
    /// @return true if the guard is out of bounds, false otherwise
    [[nodiscard]] auto isGuardOutOfBounds() const -> bool {
        return guardOutOfBounds;
    }

    /// @brief Gets all positions and directions the guard has visited
    /// @return Set of visited positions with their corresponding directions
    [[nodiscard]] auto getVisitedPositions() const -> std::unordered_set<VisitedPosition> {
        return visitedPositions;
    }

    /// @brief Checks if the guard has returned to a previously visited position and direction
    /// @return true if a loop is detected, false otherwise
    [[nodiscard]] auto guardLoopsAround() const -> bool;

    /// @brief Gets all empty positions in the map
    /// @return Vector of {row, col} pairs representing empty tiles
    [[nodiscard]] auto getFreePositions() const -> std::vector<std::pair<size_t, size_t>>;

    /// @brief Places an obstacle at the specified position
    /// @param position The {row, col} position where to place the obstacle
    void insertObstacle(std::pair<size_t, size_t> position) {
        map[position.first][position.second] = TileType::Obstacle;
    }

  private:
    [[nodiscard]] auto tryMoveUp(size_t row, size_t col) const -> MovementResult;
    [[nodiscard]] auto tryMoveDown(size_t row, size_t col) const -> MovementResult;
    [[nodiscard]] auto tryMoveLeft(size_t row, size_t col) const -> MovementResult;
    [[nodiscard]] auto tryMoveRight(size_t row, size_t col) const -> MovementResult;
    [[nodiscard]] auto calculateNewPosition(size_t row, size_t col) const -> std::pair<int64_t, int64_t>;
    void updateGuardPosition(size_t row, size_t col, MovementResult result, FacingDirection newDirection);

    std::vector<std::vector<TileType>> map;
    std::pair<int64_t, int64_t> guardPosition;
    FacingDirection guardDirection;
    bool guardOutOfBounds = false;
    std::unordered_set<VisitedPosition, std::hash<VisitedPosition>> visitedPositions;
};

} // namespace aoc::day_6

template <> struct std::formatter<aoc::day_6::PuzzleMap> : std::formatter<std::string_view> {
    [[nodiscard]] auto format(aoc::day_6::PuzzleMap map, format_context & ctx) const {
        return formatter<string_view>::format(map.toString(), ctx);
    }
};