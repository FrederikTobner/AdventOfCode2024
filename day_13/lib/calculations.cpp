#include "calculations.hpp"

#include <optional>
#include <string>

#include "../../shared/src/vector2d.hpp"

#include "../../shared/src/equation.hpp"

namespace aoc::day_13 {

struct claw_machine_state {
    aoc::math::vector_2d<size_t> button_a{0, 0};
    aoc::math::vector_2d<size_t> button_b{0, 0};
    aoc::math::vector_2d<size_t> price{0, 0};
};

static auto parseCoordinates(std::string_view line) -> aoc::math::vector_2d<size_t> {
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
    return {x.value(), y.value()};
}

static auto processTriplet(claw_machine_state & state, size_t const & increment) -> size_t {
    state.price.x += increment;
    state.price.y += increment;

    auto cheapestResult = aoc::math::solveEquationsWithTwoUnknows(state.button_a, state.button_b, state.price);
    if (cheapestResult.has_value()) {
        return cheapestResult->first * BUTTON_A_PUSH_COST + cheapestResult->second * BUTTON_B_PUSH_COST;
    }
    return 0;
}

auto calculateTotalPrice(std::vector<std::string_view> lines, size_t const & increment) -> size_t {
    claw_machine_state state;
    size_t tokens_spent = 0;

    for (size_t i = 0; i < lines.size(); ++i) {
        auto coords = parseCoordinates(lines[i]);
        auto vector = aoc::math::vector_2d<size_t>{coords.x, coords.y};

        switch (i % 3) {
        case 0:
            state.button_a = vector;
            break;
        case 1:
            state.button_b = vector;
            break;
        case 2:
            state.price = vector;
            tokens_spent += processTriplet(state, increment);
            break;
        }
    }
    return tokens_spent;
}

} // namespace aoc::day_13