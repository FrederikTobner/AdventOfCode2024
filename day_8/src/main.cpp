#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <execution>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/coordinate.hpp"

void renderResult(std::vector<std::string_view> lines, std::multimap<char, aoc::day_8::coordinate> antinodes) {
    std::string output = "";
    std::unordered_set<aoc::day_8::coordinate> antinodes_set = {};
    for (auto const & antinode : antinodes) {
        antinodes_set.insert(antinode.second);
    }

    for (auto x : std::views::iota(int64_t{0}, static_cast<int64_t>(lines.size()))) {
        for (auto y : std::views::iota(int64_t{0}, static_cast<int64_t>(lines[x].size()))) {
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

/// @brief Checks for every antenna the antinodes
/// @details These are points that are twice as far away from the second antenna as the distance to the first antenna
/// and the antinode and have the same frequency as the antenna. They need to be not blocked by any other antenna
/// @param lines The grid
/// @param antenas The antennas
/// @return The antinodes
std::multimap<char, aoc::day_8::coordinate> determineAntinodes(int64_t max_x, int64_t max_y,
                                                               std::multimap<char, aoc::day_8::coordinate> antenas) {
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
                auto x_diff = second_x - first_x;
                auto y_diff = second_y - first_y;
                auto antinode_x = second_x + x_diff;
                auto antinode_y = second_y + y_diff;
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
std::multimap<char, aoc::day_8::coordinate> determineAntinodes2(int64_t max_x, int64_t max_y,
                                                                std::multimap<char, aoc::day_8::coordinate> antenas) {
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
                auto x_diff = second_x - first_x;
                auto y_diff = second_y - first_y;
                auto current_x_diff = x_diff;
                auto current_y_diff = y_diff;
                while (true) {
                    auto antinode_x = second_x + current_x_diff;
                    auto antinode_y = second_y + current_y_diff;
                    if (antinode_x < 0 || antinode_x >= max_x || antinode_y < 0 || antinode_y >= max_y) {
                        break;
                    }
                    antinodes.insert({frequency, {antinode_x, antinode_y}});
                    current_x_diff += x_diff;
                    current_y_diff += y_diff;
                }
                current_x_diff = -x_diff;
                current_y_diff = -y_diff;
                while (true) {
                    auto antinode_x = second_x + current_x_diff;
                    auto antinode_y = second_y + current_y_diff;
                    if (antinode_x < 0 || antinode_x >= max_x || antinode_y < 0 || antinode_y >= max_y) {
                        break;
                    }
                    antinodes.insert({frequency, {antinode_x, antinode_y}});
                    current_x_diff -= x_diff;
                    current_y_diff -= y_diff;
                }
            }
        }
    }

    return antinodes;
}

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::vector<std::string_view> lines = aoc::grid_processor::processLines(*input);
    if (!aoc::grid_processor::validateGrid(lines)) {
        std::println(stderr, "Lines have different lengths");
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    std::multimap<char, aoc::day_8::coordinate> antenas;
    for (auto x : std::views::iota(int64_t{0}, static_cast<int64_t>(lines.size()))) {
        for (auto y : std::views::iota(int64_t{0}, static_cast<int64_t>(lines[x].size()))) {
            if (std::isalnum(lines[x][y])) {
                antenas.insert({lines[x][y], {x, y}});
            }
        }
    }
    int64_t max_x = lines.size();
    int64_t max_y = lines[0].size();

    // Part 1
    std::multimap<char, aoc::day_8::coordinate> antinodes = determineAntinodes(max_x, max_y, antenas);

    renderResult(lines, antinodes);

    // Part 2
    std::multimap<char, aoc::day_8::coordinate> antinodes2 = determineAntinodes2(max_x, max_y, antenas);

    renderResult(lines, antinodes2);

    return 0;
}
