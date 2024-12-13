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

/// @brief Calculate the cheapest result for the given button pushes and prize
/// @details The cheapest result is calculated using Cramer's rule
/// @param button_a The translation vector for button A
/// @param button_b The translation vector for button B
/// @param prize The location of the prize
/// @return The cheapest result or std::nullopt if no solution exists
std::optional<result> calculateCheapestResult(aoc::math::vector_2d<size_t> const & button_a,
                                              aoc::math::vector_2d<size_t> const & button_b,
                                              aoc::math::vector_2d<size_t> const & prize) {

    double determinant = static_cast<double>(button_a.x) * button_b.y - static_cast<double>(button_a.y) * button_b.x;

    if (determinant == 0) {
        return std::nullopt;
    }

    double a = (static_cast<double>(prize.x) * button_b.y - static_cast<double>(prize.y) * button_b.x) / determinant;
    double b = (static_cast<double>(button_a.x) * prize.y - static_cast<double>(button_a.y) * prize.x) / determinant;

    if (a < 0 || b < 0 || a != std::floor(a) || b != std::floor(b)) {
        return std::nullopt;
    }

    size_t button_a_pushes = static_cast<size_t>(a);
    size_t button_b_pushes = static_cast<size_t>(b);

    if (button_a_pushes * button_a.x + button_b_pushes * button_b.x != prize.x ||
        button_a_pushes * button_a.y + button_b_pushes * button_b.y != prize.y) {
        return std::nullopt;
    }

    return result{button_a_pushes, button_b_pushes};
}

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
            auto cheapestResult = aoc::day_13::calculateCheapestResult(button_a, button_b, price);
            if (cheapestResult.has_value()) {
                tokens_spent += cheapestResult->button_a_pushes * BUTTON_A_PUSH_COST +
                                cheapestResult->button_b_pushes * BUTTON_B_PUSH_COST;
            }
            break;
        }
    }
    return tokens_spent;
}

} // namespace aoc::day_13