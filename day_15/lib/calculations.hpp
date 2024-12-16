#pragma once

#include <cstdint>
#include <vector>

#include "cell_type.hpp"

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_15 {

auto calculate_gps_coordinate(aoc::math::vector_2d<size_t> const & box) -> size_t {
    return box.y * 100 + box.x;
}

// Calculates the gps coordinate of each box which is 100 times its distance from the top edge of the map plus its
// distance from the left edge of the map.
auto calculate_gps_sum(std::vector<std::vector<cell_type>> & warehouse) -> size_t {
    size_t sum = 0;

    for (size_t y = 0; y < warehouse.size(); ++y) {
        for (size_t x = 0; x < warehouse[y].size(); ++x) {
            if (warehouse[y][x] == cell_type::box) {
                sum += calculate_gps_coordinate({x, y});
            }
        }
    }

    return sum;
}

} // namespace aoc::day_15