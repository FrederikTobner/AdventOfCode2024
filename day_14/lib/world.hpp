#pragma once

#include <cstdint>
#include <vector>

#include "robots.hpp"

namespace aoc::day_14 {

struct world {
    std::vector<robot> robots;
    size_t x_size;
    size_t y_size;

    auto update() -> void {
        for (auto & r : robots) {
            r.update(x_size, y_size);
        }
    }

    auto safetyScore() const -> size_t {
        // To determine the safest area, count the number of robots in each quadrant after 100 seconds. Robots that are
        // exactly in the middle (horizontally or vertically) don't count as being in any quadrant.
        size_t top_left = 0;
        size_t top_right = 0;
        size_t bottom_left = 0;
        size_t bottom_right = 0;

        for (auto const & r : robots) {
            if (r.position.x < x_size / 2 && r.position.y < y_size / 2) {
                ++top_left;
            } else if (r.position.x >= x_size / 2 + 1 && r.position.y < y_size / 2) {
                ++top_right;
            } else if (r.position.x < x_size / 2 && r.position.y >= y_size / 2 + 1) {
                ++bottom_left;
            } else if (r.position.x >= x_size / 2 + 1 && r.position.y >= y_size / 2 + 1) {
                ++bottom_right;
            }
        }
        return top_left * top_right * bottom_left * bottom_right;
    }
};

} // namespace aoc::day_14