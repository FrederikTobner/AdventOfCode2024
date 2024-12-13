#pragma once

#include <array>
#include <cstdint>

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_12 {

enum class Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT,
    UP_RIGHT,
    DOWN_RIGHT,
    DOWN_LEFT,
    UP_LEFT,
};

[[nodiscard]] constexpr auto getDirectionVector(Direction direction) -> aoc::math::vector_2d<int16_t> {
    switch (direction) {
    case Direction::UP:
        return {0, -1};
    case Direction::RIGHT:
        return {1, 0};
    case Direction::DOWN:
        return {0, 1};
    case Direction::LEFT:
        return {-1, 0};
    case Direction::UP_RIGHT:
        return {1, -1};
    case Direction::DOWN_RIGHT:
        return {1, 1};
    case Direction::DOWN_LEFT:
        return {-1, 1};
    case Direction::UP_LEFT:
        return {-1, -1};
    default:
        throw std::invalid_argument("Invalid direction");
    }
}

[[nodiscard]] constexpr auto getDirections() -> std::array<Direction, 4> {
    return {Direction::UP, Direction::RIGHT, Direction::DOWN, Direction::LEFT};
}

[[nodiscard]] constexpr auto getDiagonalDirections() -> std::array<Direction, 4> {
    return {Direction::UP_RIGHT, Direction::DOWN_RIGHT, Direction::DOWN_LEFT, Direction::UP_LEFT};
}
} // namespace aoc::day_12