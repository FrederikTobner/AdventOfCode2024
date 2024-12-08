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

#include "../lib/coordinate.hpp"

namespace aoc::day_8 {
auto renderResult(std::vector<std::string_view> lines, std::unordered_set<aoc::day_8::coordinate> antinodes,
                  int64_t max_x_coordinate, int64_t max_y_coordinate) -> void {
    std::string output = "";
    for (auto x : std::views::iota(int64_t{0}, max_y_coordinate)) {
        for (auto y : std::views::iota(int64_t{0}, max_x_coordinate)) {
            if (antinodes.contains({x, y})) {
                output += '#';
            } else {
                output += lines[x][y];
            }
        }
        output += '\n';
    }
    std::println("Result:\n{}Found {} antinodes", output, antinodes.size());
}
} // namespace aoc::day_8