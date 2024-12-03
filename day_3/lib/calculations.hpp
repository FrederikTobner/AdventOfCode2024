#pragma once

#include <concepts>
#include <cstdint>
#include <ranges>
#include <utility>
#include <vector>

#include "../../shared/ranges_compatibility_layer.hpp"

namespace aoc::calculations {

template <typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

template <Numeric T = uint64_t> auto accumulateProducts(std::ranges::range auto const & matches) {
    // Accumulations are commutative, so we can use parallel execution and process the results out of order
    return aoc::ranges::fold_left(std::execution::par_unseq, matches, T{0},
                                  [](auto acc, auto const & pair) { return acc + pair.first * pair.second; });
}

} // namespace aoc::calculations