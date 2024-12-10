#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_8 {
/// @brief Renders the map with antinodes marked as '#'
/// @param lines Original map lines
/// @param antinodes Set of antinode positions to render
/// @param max_x_coordinate Maximum x coordinate (exclusive)
/// @param max_y_coordinate Maximum y coordinate (exclusive)
auto renderResult(std::vector<std::string_view> lines, std::unordered_set<aoc::math::Vector2D<int64_t>> antinodes,
                  int64_t max_x_coordinate, int64_t max_y_coordinate) -> void {
    auto to_char = [&](aoc::math::Vector2D<int64_t> pos) {
        return antinodes.contains(pos) ? '#' : lines[pos.x][pos.y];
    };

    auto grid = std::views::cartesian_product(std::views::iota(int64_t{0}, max_y_coordinate),
                                              std::views::iota(int64_t{0}, max_x_coordinate)) |
                std::views::chunk_by([](auto a, auto b) { return std::get<0>(a) == std::get<0>(b); }) |
                std::views::transform([&](auto row) {
                    return std::views::transform(row,
                                                 [&](auto pos) {
                                                     return to_char({std::get<0>(pos), std::get<1>(pos)});
                                                 }) |
                           std::views::common;
                });

    for (auto row : grid) {
        std::println("{}", row | aoc::ranges::to<std::string>);
    }
    std::println("Found {} antinodes", antinodes.size());
}
} // namespace aoc::day_8