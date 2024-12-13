#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include "../../shared/src/vector2d.hpp"

#include "linear_algebra.hpp"

namespace aoc::day_13 {

#define BUTTON_A_PUSH_COST 3
#define BUTTON_B_PUSH_COST 1

/// @brief Calculate the total price for the given lines
/// @param lines The lines to calculate the total price for
/// @param increment The increment for the price
/// @return The total price
size_t calculateTotalPrice(std::vector<std::string_view> lines, size_t increment) {
    auto button_a = aoc::math::vector_2d<size_t>{0, 0};
    auto button_b = aoc::math::vector_2d<size_t>{0, 0};
    auto price = aoc::math::vector_2d<size_t>{0, 0};
    size_t line_amount = std::ranges::size(lines);
    size_t tokens_spent = 0;
    for (size_t i = 0; i < line_amount; ++i) {
        auto line = lines[i];
        std::optional<size_t> x;
        std::optional<size_t> y;
        size_t currentIndex = 0;
        while (currentIndex < line.size()) {
            if (std::isdigit(line[currentIndex])) {
                if (!x.has_value()) {
                    x = (line[currentIndex] - '0');
                    while (++currentIndex < line.size() && std::isdigit(line[currentIndex])) {
                        x = x.value() * 10 + (line[currentIndex] - '0');
                    }
                } else {
                    y = (line[currentIndex] - '0');
                    while (++currentIndex < line.size() && std::isdigit(line[currentIndex])) {
                        y = y.value() * 10 + (line[currentIndex] - '0');
                    }
                }
            }
            currentIndex++;
        }
        switch (i % 3) {
        case 0:
            button_a = {x.value(), y.value()};
            break;
        case 1:
            button_b = {x.value(), y.value()};
            break;
        case 2:
            price = {x.value() + increment, y.value() + increment};
            auto cheapestResult = aoc::day_13::solveEquationsWithTwoUnknows(button_a, button_b, price);
            if (cheapestResult.has_value()) {
                tokens_spent +=
                    cheapestResult->first * BUTTON_A_PUSH_COST + cheapestResult->second * BUTTON_B_PUSH_COST;
            }
            break;
        }
    }
    return tokens_spent;
}

} // namespace aoc::day_13