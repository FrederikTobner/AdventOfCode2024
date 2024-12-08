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

/// @brief Checks for every antenna the antinodes
/// @details These are points that are twice as far away from the second antenna as the distance to the first antenna
/// and the antinode and have the same frequency as the antenna. They need to be not blocked by any other antenna
/// @param lines The grid
/// @param antenas The antennas
/// @return The antinodes
auto determineAntinodes(int64_t max_x, int64_t max_y, std::multimap<char, aoc::day_8::coordinate> antenas)
    -> std::multimap<char, aoc::day_8::coordinate> {
    std::multimap<char, aoc::day_8::coordinate> antinodes;
    for (auto const & antenna : antenas) {
        char frequency = antenna.first;
        // Get all other antennas with the same frequency
        auto [start, end] = antenas.equal_range(frequency);
        std::vector<aoc::day_8::coordinate> same_frequency;
        for (auto it = start; it != end; ++it) {
            // Make sure we dont add the same antenna to the list
            if (it->second != antenna.second) {
                auto [second_x, second_y] = it->second;
                auto [first_x, first_y] = antenna.second;
                // mirror the distance between the antenna and the antinode
                int64_t x_diff = second_x - first_x;
                int64_t y_diff = second_y - first_y;
                int64_t antinode_x = second_x + x_diff;
                int64_t antinode_y = second_y + y_diff;
                if (antinode_x >= 0 && antinode_x < max_x && antinode_y >= 0 && antinode_y < max_y) {
                    antinodes.insert({frequency, {antinode_x, antinode_y}});
                }
            }
        }
    }
    return antinodes;
}

/// @brief Checks for every antenna the antinodes without the need to have them twice as far away from the second
/// antenna as the distance between the first and the second antenna. t any grid position exactly in line with at least
/// two antennas of the same frequency, regardless of distance a antinode occurs
auto determineAntinodes2(int64_t max_x, int64_t max_y, std::multimap<char, aoc::day_8::coordinate> antenas)
    -> std::multimap<char, aoc::day_8::coordinate> {
    std::multimap<char, aoc::day_8::coordinate> antinodes;
    for (auto const & antenna : antenas) {
        char frequency = antenna.first;
        // Get all other antennas with the same frequency
        auto [start, end] = antenas.equal_range(frequency);
        std::vector<aoc::day_8::coordinate> same_frequency;
        for (auto it = start; it != end; ++it) {
            // Make sure we dont add the same antenna to the list
            if (it->second != antenna.second) {
                auto [second_x, second_y] = it->second;
                auto [first_x, first_y] = antenna.second;
                // mirror the distance between the antenna and the antinode
                int64_t x_diff = second_x - first_x;
                int64_t y_diff = second_y - first_y;
                int64_t antinode_x = second_x;
                int64_t antinode_y = second_y;
                while (!(antinode_x < 0 || antinode_x >= max_x || antinode_y < 0 || antinode_y >= max_y)) {
                    antinodes.insert({frequency, {antinode_x, antinode_y}});
                    antinode_x += x_diff;
                    antinode_y += y_diff;
                }
            }
        }
    }

    return antinodes;
}

} // namespace aoc::day_8