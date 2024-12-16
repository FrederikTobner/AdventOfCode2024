#pragma once

namespace aoc::day_15 {

enum class cell_type {
    empty,         // .
    wall,          // #
    box,           // O
    robot,         // @
    box_part_left, // [
    box_part_right // ]
};

} // namespace aoc::day_15