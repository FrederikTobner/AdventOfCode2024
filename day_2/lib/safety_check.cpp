#include "safety_check.hpp"
#include <algorithm>
#include <ranges>
#include <vector>

#include "../../shared/src/ranges_compatibility_layer.hpp"

namespace aoc::day_2 {

auto isSafe(std::span<uint8_t const> input) -> bool {
    return std::ranges::adjacent_find(input, [](uint8_t a, uint8_t b) { return a == b || std::abs(a - b) > 3; }) ==
               input.end() &&
           !std::ranges::any_of(std::views::adjacent<3>(input), [](auto triple) {
               auto [first, second, third] = triple;
               return (second > first && second > third) || (second < first && second < third);
           });
}

auto canBeMadeSafe(std::span<uint8_t const> input) -> bool {
    return std::ranges::any_of(std::views::iota(0u, input.size()), [&](size_t index) {
        return isSafe(input | std::views::enumerate |
                      std::views::filter([index](const auto & pair) { return std::get<0>(pair) != index; }) |
                      std::views::transform([](const auto & pair) { return std::get<1>(pair); }) |
                      aoc::ranges::to<std::vector<uint8_t>>);
    });
}

} // namespace aoc::day_2