#pragma once

#include <span>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace aoc::day_6 {

enum class TileType {
    Empty,   // .
    Guard,   // ^ up, v down, < left, > right
    Obstacle // #
};

enum FacingDirection {
    Up,
    Down,
    Left,
    Right
};

struct VisitedPosition {
    size_t row;
    size_t col;
    FacingDirection direction;

    // Spaceship operator
    auto operator<=>(VisitedPosition const &) const = default;
};

/// @brief A Map storing a 2D grid of
class PuzzleMap {

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
        auto visitedPosition =
            VisitedPosition(this->guardPosition.first, this->guardPosition.second, this->guardDirection);
        visitedPositions.insert(visitedPosition);
        map[guardPosition.first][guardPosition.second] = TileType::Empty;
        auto [row, col] = guardPosition;
        switch (guardDirection) {
        case FacingDirection::Up:
            if (row == 0) {
                guardOutOfBounds = true;
            } else if (map[row - 1][col] == TileType::Obstacle) {
                guardDirection = FacingDirection::Right;
            } else {
                guardPosition = {row - 1, col};
            }
            break;
        case FacingDirection::Down:
            if (row == map.size() - 1) {
                guardOutOfBounds = true;
            } else if (map[row + 1][col] == TileType::Obstacle) {
                guardDirection = FacingDirection::Left;
            } else {
                guardPosition = {row + 1, col};
            }
            break;
        case FacingDirection::Left:
            if (col == 0) {
                guardOutOfBounds = true;
            } else if (map[row][col - 1] == TileType::Obstacle) {
                guardDirection = FacingDirection::Up;
            } else {
                guardPosition = {row, col - 1};
            }
            break;
        case FacingDirection::Right:
            if (col == map[row].size() - 1) {
                guardOutOfBounds = true;
            } else if (map[row][col + 1] == TileType::Obstacle) {
                guardDirection = FacingDirection::Down;
            } else {
                guardPosition = {row, col + 1};
            }
            break;
        }
        if (guardPosition.first >= map.size() || guardPosition.second >= map[guardPosition.first].size()) {
            guardOutOfBounds = true;
        } else if (guardPosition.first < 0 || guardPosition.second < 0) {
            guardOutOfBounds = true;
        } else {
            map[guardPosition.first][guardPosition.second] = TileType::Guard;
        }
        if (row != guardPosition.first || col != guardPosition.second) {
            map[row][col] = TileType::Empty;
            map[guardPosition.first][guardPosition.second] = TileType::Guard;
            return !guardLoopsAround();
        }
        return true;
    }

    bool isGuardOutOfBounds() const {
        return guardOutOfBounds;
    }

    [[nodiscard]] auto getVisitedPositions() const -> std::set<VisitedPosition> {
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
    std::set<VisitedPosition> visitedPositions;
};

} // namespace aoc::day_6
