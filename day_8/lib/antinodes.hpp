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

#include "../lib/coordinate.hpp"

namespace aoc::day_8 {

namespace detail {
static [[nodiscard]] auto getAntennasByFrequency(char frequency, coordinate const & exclude_pos,
                                                 std::multimap<char, coordinate> const & antenas) {
    auto [start, end] = antenas.equal_range(frequency);
    std::vector<std::pair<char const, coordinate>> temp;
    for (auto it = start; it != end; ++it) {
        if (it->second != exclude_pos) {
            temp.push_back({it->first, it->second});
        }
    }
    return temp;
}
} // namespace detail

[[nodiscard]] auto determineAntinodes(int64_t max_x_coordinate, int64_t max_y_coordinate,
                                      std::multimap<char, coordinate> antenas) -> std::unordered_set<coordinate> {
    std::unordered_set<coordinate> antinodes;
    for (auto const & [frequency, pos] : antenas) {
        for (auto const & other : detail::getAntennasByFrequency(frequency, pos, antenas)) {
            aoc::day_8::coordinate diff = other.second - pos;
            aoc::day_8::coordinate calculated_antinode = other.second + diff;
            if (calculated_antinode.in_bounds(max_x_coordinate, max_y_coordinate)) {
                antinodes.emplace(calculated_antinode);
            }
        }
    }
    return antinodes;
}

[[nodiscard]] auto determineAntinodes2(int64_t max_x_coordinate, int64_t max_y_coordinate,
                                       std::multimap<char, coordinate> antenas) -> std::unordered_set<coordinate> {
    std::unordered_set<coordinate> antinodes;
    for (auto const & [frequency, pos] : antenas) {
        for (auto const & other : detail::getAntennasByFrequency(frequency, pos, antenas)) {
            aoc::day_8::coordinate diff = other.second - pos;
            for (aoc::day_8::coordinate upcoming_antinode = other.second;
                 upcoming_antinode.in_bounds(max_x_coordinate, max_y_coordinate); upcoming_antinode += diff) {
                antinodes.emplace(upcoming_antinode);
            }
        }
    }
    return antinodes;
}

} // namespace aoc::day_8