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

    [[nodiscard]] auto formsChristmasTree() const -> bool {
        std::vector<std::vector<size_t>> density(y_size, std::vector<size_t>(x_size, 0));

        for (auto const & r : robots) {
            density[r.position.y][r.position.x]++;
        }

        for (size_t y = 0; y < y_size; ++y) {
            for (size_t x = 0; x < x_size; ++x) {
                if (density[y][x] > 1) {
                    return false;
                }
            }
        }
        return true;
    }
};

} // namespace aoc::day_14