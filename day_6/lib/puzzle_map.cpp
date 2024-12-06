
#include "puzzle_map.hpp"
#include <stdexcept>

namespace aoc::day_6 {

PuzzleMap::PuzzleMap(std::vector<std::vector<TileType>> grid, std::pair<int64_t, int64_t> startPosition,
                     FacingDirection startDirection)
    : map(std::move(grid)), guardPosition(startPosition), guardDirection(startDirection) {
}

auto PuzzleMap::toString() const -> std::string {
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

auto PuzzleMap::tryMoveUp(size_t row, size_t col) const -> MovementResult {
    if (row == 0) {
        return MovementResult::OutOfBounds;
    }
    return map[row - 1][col] == TileType::Obstacle ? MovementResult::Blocked : MovementResult::Moved;
}

auto PuzzleMap::tryMoveDown(size_t row, size_t col) const -> MovementResult {
    if (row == map.size() - 1) {
        return MovementResult::OutOfBounds;
    }
    return map[row + 1][col] == TileType::Obstacle ? MovementResult::Blocked : MovementResult::Moved;
}

auto PuzzleMap::tryMoveLeft(size_t row, size_t col) const -> MovementResult {
    if (col == 0) {
        return MovementResult::OutOfBounds;
    }
    return map[row][col - 1] == TileType::Obstacle ? MovementResult::Blocked : MovementResult::Moved;
}

auto PuzzleMap::tryMoveRight(size_t row, size_t col) const -> MovementResult {
    if (col == map[row].size() - 1) {
        return MovementResult::OutOfBounds;
    }
    return map[row][col + 1] == TileType::Obstacle ? MovementResult::Blocked : MovementResult::Moved;
}

auto PuzzleMap::calculateNewPosition(size_t row, size_t col) const -> std::pair<int64_t, int64_t> {
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

void PuzzleMap::updateGuardPosition(size_t row, size_t col, MovementResult result, FacingDirection newDirection) {
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

bool PuzzleMap::update() {
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

auto PuzzleMap::guardLoopsAround() const -> bool {
    auto currentPos = VisitedPosition(guardPosition.first, guardPosition.second, guardDirection);
    return visitedPositions.contains(currentPos);
}

auto PuzzleMap::getFreePositions() const -> std::vector<std::pair<size_t, size_t>> {
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

} // namespace aoc::day_6