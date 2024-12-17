#pragma once

namespace aoc::day_15 {

/// @brief The different types of cells in the warehouse
enum class cell_type {
    EMPTY,         // .
    WALL,          // #
    BOX,           // O
    ROBOT,         // @
    BOX_PART_LEFT, // [
    BOX_PART_RIGHT // ]
};

} // namespace aoc::day_15