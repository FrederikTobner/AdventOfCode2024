#include "safety_check.hpp"
#include <algorithm>
#include <ranges>

#include "../../shared/ranges_compatibility_layer.hpp"

namespace safety_check {

bool isSafe(std::span<uint8_t const> input) {
    if (input.size() < 2) {
        return true;
    }

    return std::ranges::adjacent_find(input, [](uint8_t a, uint8_t b) { return a == b || std::abs(a - b) > 3; }) ==
               input.end() &&
           !std::ranges::any_of(std::views::adjacent<3>(input), [](auto triple) {
               auto [a, b, c] = triple;
               return (b > a && b > c) || (b < a && b < c);
           });
}

bool canBeMadeSafe(std::span<uint8_t const> input) {
    return std::ranges::any_of(std::views::iota(0u, input.size()), [&](size_t i) {
        auto removed =
            nonstd::ranges::to_vector(input | std::views::enumerate |
                                      std::views::filter([i](const auto & pair) { return std::get<0>(pair) != i; }) |
                                      std::views::transform([](const auto & pair) { return std::get<1>(pair); }));
        return isSafe(removed);
    });
}

} // namespace safety_check