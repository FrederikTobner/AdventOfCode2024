#pragma once

namespace aoc::day_6 {

enum class TileType {
    Empty,   // .
    Guard,   // ^ up, v down, < left, > right
    Obstacle // #
};

} // namespace aoc::day_6