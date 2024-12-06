#pragma once

#include <span>
#include <string>
#include <string_view>
#include <unordered_set>
#include <utility>
#include <vector>

#include "facing_direction.hpp"
#include "tile_type.hpp"
#include "visited_position.hpp"

namespace aoc::day_6 {

// New enum for movement results
enum class MovementResult {
    Moved,
    Blocked,
    OutOfBounds
};

/// @brief A Map storing a 2D grid of tiles
class PuzzleMap {

    // Helper methods for movement
    [[nodiscard]] auto tryMoveUp(size_t row, size_t col) const -> MovementResult {
        if (row == 0) {
            return MovementResult::OutOfBounds;
        }
        if (map[row - 1][col] == TileType::Obstacle) {
            return MovementResult::Blocked;
        }
        return MovementResult::Moved;
    }

    [[nodiscard]] auto tryMoveDown(size_t row, size_t col) const -> MovementResult {
        if (row == map.size() - 1) {
            return MovementResult::OutOfBounds;
        }
        if (map[row + 1][col] == TileType::Obstacle) {
            return MovementResult::Blocked;
        }
        return MovementResult::Moved;
    }

    [[nodiscard]] auto tryMoveLeft(size_t row, size_t col) const -> MovementResult {
        if (col == 0) {
            return MovementResult::OutOfBounds;
        }
        if (map[row][col - 1] == TileType::Obstacle) {
            return MovementResult::Blocked;
        }
        return MovementResult::Moved;
    }

    [[nodiscard]] auto tryMoveRight(size_t row, size_t col) const -> MovementResult {
        if (col == map[row].size() - 1) {
            return MovementResult::OutOfBounds;
        }
        if (map[row][col + 1] == TileType::Obstacle) {
            return MovementResult::Blocked;
        }
        return MovementResult::Moved;
    }

    [[nodiscard]] auto calculateNewPosition(size_t row, size_t col) const -> std::pair<int64_t, int64_t> {
        switch (guardDirection) {
        case FacingDirection::Up:
            return {row - 1, col};
        case FacingDirection::Down:
            return {row + 1, col};
        case FacingDirection::Left:
            return {row, col - 1};
        case FacingDirection::Right:
            return {row, col + 1};
        }
        throw std::runtime_error("Invalid direction");
    }

    void updateGuardPosition(size_t row, size_t col, MovementResult result, FacingDirection newDirection) {
        switch (result) {
        case MovementResult::OutOfBounds:
            guardOutOfBounds = true;
            break;
        case MovementResult::Blocked:
            guardDirection = newDirection;
            break;
        case MovementResult::Moved:
            map[row][col] = TileType::Empty;
            guardPosition = calculateNewPosition(row, col);
            map[guardPosition.first][guardPosition.second] = TileType::Guard;
            break;
        }
    }

  public:
    PuzzleMap(std::span<std::string_view const> grid) {
        map.reserve(grid.size());
        for (auto row : grid) {
            std::vector<TileType> rowTiles;
            rowTiles.reserve(row.size());
            for (auto tile : row) {
                switch (tile) {
                case '.':
                    rowTiles.push_back(TileType::Empty);
                    break;
                case '^':
                    rowTiles.push_back(TileType::Guard);
                    guardPosition = {map.size(), rowTiles.size() - 1};
                    guardDirection = FacingDirection::Up;
                    break;
                case 'v':
                    rowTiles.push_back(TileType::Guard);
                    guardPosition = {map.size(), rowTiles.size() - 1};
                    guardDirection = FacingDirection::Down;
                    break;
                case '<':
                    rowTiles.push_back(TileType::Guard);
                    guardPosition = {map.size(), rowTiles.size() - 1};
                    guardDirection = FacingDirection::Left;
                    break;
                case '>':
                    rowTiles.push_back(TileType::Guard);
                    guardPosition = {map.size(), rowTiles.size() - 1};
                    guardDirection = FacingDirection::Right;
                    break;
                case '#':
                    rowTiles.push_back(TileType::Obstacle);
                    break;
                default:
                    throw std::invalid_argument("Invalid tile type");
                }
            }
            map.push_back(std::move(rowTiles));
        }
    }

    /// @brief Creates a output string representation of the map
    [[nodiscard]] auto toString() const -> std::string {
        std::string output;
        for (auto const & row : map) {
            for (auto const tile : row) {
                switch (tile) {
                case TileType::Empty:
                    output.push_back('.');
                    break;
                case TileType::Guard:
                    switch (guardDirection) {
                    case FacingDirection::Up:
                        output.push_back('^');
                        break;
                    case FacingDirection::Down:
                        output.push_back('v');
                        break;
                    case FacingDirection::Left:
                        output.push_back('<');
                        break;
                    case FacingDirection::Right:
                        output.push_back('>');
                        break;
                    }
                    break;
                case TileType::Obstacle:
                    output.push_back('#');
                    break;
                }
            }
            output.push_back('\n');
        }
        return output;
    }

    // Updates the map state based on the current player position
    // If there are no obstacles in the player's path, the player moves forward (So the direction he is facing in)
    // If the path is blocked, the player turns right
    bool update() {
        if (guardOutOfBounds) {
            return true;
        }

        auto [row, col] = guardPosition;
        visitedPositions.insert(VisitedPosition{static_cast<size_t>(row), static_cast<size_t>(col), guardDirection});

        MovementResult result;
        FacingDirection newDirection;

        switch (guardDirection) {
        case FacingDirection::Up:
            result = tryMoveUp(row, col);
            newDirection = FacingDirection::Right;
            break;
        case FacingDirection::Down:
            result = tryMoveDown(row, col);
            newDirection = FacingDirection::Left;
            break;
        case FacingDirection::Left:
            result = tryMoveLeft(row, col);
            newDirection = FacingDirection::Up;
            break;
        case FacingDirection::Right:
            result = tryMoveRight(row, col);
            newDirection = FacingDirection::Down;
            break;
        }

        updateGuardPosition(row, col, result, newDirection);
        return result == MovementResult::Moved ? !guardLoopsAround() : true;
    }

    bool isGuardOutOfBounds() const {
        return guardOutOfBounds;
    }

    [[nodiscard]] auto getVisitedPositions() const -> std::unordered_set<VisitedPosition> {
        return visitedPositions;
    }

    bool guardLoopsAround() const {
        auto currentPos = VisitedPosition(guardPosition.first, guardPosition.second, guardDirection);
        return visitedPositions.contains(currentPos);
    }

    std::vector<std::pair<size_t, size_t>> getFreePositions() const {
        std::vector<std::pair<size_t, size_t>> freePositions;
        for (size_t row = 0; row < map.size(); ++row) {
            for (size_t col = 0; col < map[row].size(); ++col) {
                if (map[row][col] == TileType::Empty) {
                    freePositions.push_back({row, col});
                }
            }
        }
        return freePositions;
    }

    void insertObstacle(std::pair<size_t, size_t> position) {
        map[position.first][position.second] = TileType::Obstacle;
    }

  private:
    std::vector<std::vector<TileType>> map;
    std::pair<int64_t, int64_t> guardPosition;
    FacingDirection guardDirection;
    bool guardOutOfBounds = false;
    std::unordered_set<VisitedPosition, std::hash<VisitedPosition>> visitedPositions;
};

} // namespace aoc::day_6

/// @brief Formatter for the PuzzleMap class
template <> struct std::formatter<aoc::day_6::PuzzleMap> : std::formatter<std::string_view> {
    [[nodiscard]] auto format(aoc::day_6::PuzzleMap map, format_context & ctx) const {
        return formatter<string_view>::format(map.toString(), ctx);
    }
};