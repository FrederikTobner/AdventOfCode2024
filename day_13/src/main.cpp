
#include <expected>
#include <ranges>
#include <string>
#include <system_error>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"
#include "../../shared/src/vector2d.hpp"

#include "../lib/header.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::println("{}\n", *input);

    auto lines = *input | std::views::split('\n') | std::views::transform([](auto && chars) {
        auto sv = std::string_view(chars.begin(), chars.end());
        if (sv.ends_with('\r')) {
            return sv.substr(0, sv.size() - 1);
        }
        return sv;
    }) | std::views::filter([](std::string_view sv) { return !sv.empty(); }) |
                 ::aoc::ranges::to<std::vector<std::string_view>>;

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
            price = {x.value(), y.value()};
            auto cheapestResult = aoc::day_13::calculateCheapestResult(button_a, button_b, price);
            if (cheapestResult.has_value()) {
                std::println("Button A: x:{} y:{}, Button B: x:{} y:{}, Price  x:{} y:{} - solution a:{} b:{}",
                             button_a.x, button_a.y, button_b.x, button_b.y, price.x, price.y,
                             cheapestResult->button_a_pushes, cheapestResult->button_b_pushes);
                tokens_spent += cheapestResult->button_a_pushes * BUTTON_A_PUSH_COST +
                                cheapestResult->button_b_pushes * BUTTON_B_PUSH_COST;
            } else {
                std::println("Button A: x:{} y:{}, Button B: x:{} y:{}, Price  x:{} y:{} - no solution", button_a.x,
                             button_a.y, button_b.x, button_b.y, price.x, price.y);
            }
            break;
        }
    }
    std::println("Tokens spent: {}", tokens_spent);

    return 0;
}
