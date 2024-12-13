#pragma once

#include <cstdint>
#include <optional>

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_13 {

#define BUTTON_A_PUSH_COST 3
#define BUTTON_B_PUSH_COST 1

struct result {
    size_t button_a_pushes;
    size_t button_b_pushes;
};

std::optional<result> calculateCheapestResult(aoc::math::vector_2d<size_t> const & button_a,
                                              aoc::math::vector_2d<size_t> const & button_b,
                                              aoc::math::vector_2d<size_t> const & price) {
    auto result = std::optional<aoc::day_13::result>{};
    // Based on the price, we can calculate the cheapest result.
    // The price is the amount of pushes needed to reach the price based on the button type that was pressed.
    auto upper_bound_a = std::max(price.x / button_a.x, price.y / button_a.y);
    size_t cheapestCurrentPrice = SIZE_MAX;
    for (size_t i = 0; i <= upper_bound_a; ++i) {
        auto button_a_pushes = i;
        auto upper_bound_b = std::max((price.x - button_a_pushes * button_a.x) / button_b.x,
                                      (price.y - button_a_pushes * button_a.y) / button_b.y);
        auto lower_bound_b = std::min((price.x - button_a_pushes * button_a.x) / button_b.x,
                                      (price.y - button_a_pushes * button_a.y) / button_b.y);
        for (size_t j = lower_bound_b; j <= upper_bound_b; ++j) {
            auto button_b_pushes = j;
            auto button_a_cost = button_a_pushes * BUTTON_A_PUSH_COST;
            auto button_b_cost = button_b_pushes * BUTTON_B_PUSH_COST;
            auto result_x = button_a_pushes * button_a.x + button_b_pushes * button_b.x;
            auto result_y = button_a_pushes * button_a.y + button_b_pushes * button_b.y;
            if (result_x == price.x && result_y == price.y) {
                size_t current_price = button_a_pushes * BUTTON_A_PUSH_COST + button_b_pushes * BUTTON_B_PUSH_COST;
                if (current_price < cheapestCurrentPrice) {
                    cheapestCurrentPrice = current_price;
                    result = aoc::day_13::result{button_a_pushes, button_b_pushes};
                }
            }
            // Check if we already have a higher value for x  or y
            if (result_x > price.x || result_y > price.y) {
                break;
            }
        }
    }

    return result;
}

} // namespace aoc::day_13