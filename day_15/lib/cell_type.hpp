#pragma once

namespace aoc::day_15 {

enum class cell_type {
    EMPTY,         // .
    WALL,          // #
    BOX,           // O
    ROBOT,         // @
    BOX_PART_LEFT, // [
    BOX_PART_RIGHT // ]
};

} // namespace aoc::day_15