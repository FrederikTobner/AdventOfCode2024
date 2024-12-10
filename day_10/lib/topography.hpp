#pragma once

#include <cstdint>

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_10 {

/// @brief Represents the topography of a point in a hiking trail
struct topography {
    uint8_t value;
    aoc::math::vector_2d<uint8_t> position;

    bool operator==(topography const & other) const {
        return value == other.value && position == other.position;
    }
};

} // namespace aoc::day_10