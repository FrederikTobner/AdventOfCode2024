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
void renderResult(std::vector<std::string_view> lines, std::multimap<char, aoc::day_8::coordinate> antinodes,
                  int64_t max_x, int64_t max_y) {
    std::string output = "";
    std::unordered_set<aoc::day_8::coordinate> antinodes_set = {};
    for (auto const & antinode : antinodes) {
        antinodes_set.insert(antinode.second);
    }

    for (auto x : std::views::iota(int64_t{0}, max_x)) {
        for (auto y : std::views::iota(int64_t{0}, max_y)) {
            if (antinodes_set.contains({x, y})) {
                output += '#';
            } else {
                output += lines[x][y];
            }
        }
        output += '\n';
    }
    std::println("Result:\n{}Found {} antinodes", output, antinodes_set.size());
}
} // namespace aoc::day_8