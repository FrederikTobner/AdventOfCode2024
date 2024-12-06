#pragma once

namespace aoc::day_6 {

/// @brief Represents the four cardinal directions the guard can face
/// @details Used to track the guard's orientation and determine movement direction
enum FacingDirection {
    Up,   ///< Guard is facing upward ('^' in input)
    Down, ///< Guard is facing downward ('v' in input)
    Left, ///< Guard is facing left ('<' in input)
    Right ///< Guard is facing right ('>' in input)
};

} // namespace aoc::day_6