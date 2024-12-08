#pragma once

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

#include "../lib/coordinate.hpp"

#include "../../shared/src/ranges_compatibility_layer.hpp"

namespace aoc::day_8 {

namespace detail {
/// @brief Gets positions of other antennas with the same frequency, excluding the specified position
/// @param frequency The frequency to match
/// @param exclude_pos The position to exclude from results
/// @param antenas Map of frequencies to antenna positions
/// @return Range of matching antenna positions
[[nodiscard]] static auto getOtherAntennaPositionsByFrequency(char frequency, coordinate const & exclude_pos,
                                                              std::multimap<char, coordinate> const & antenas) {
    auto range = antenas.equal_range(frequency);
    return std::ranges::subrange(range.first, range.second) |
           std::views::transform([](auto const & pair) { return pair.second; }) |
           std::views::filter([&exclude_pos](coordinate const & pos) { return pos != exclude_pos; }) |
           std::views::common;
}

/// @brief Generates a sequence of antinode positions along a line
/// @param start Starting position
/// @param diff Direction vector
/// @param max_x Maximum x coordinate (exclusive)
/// @param max_y Maximum y coordinate (exclusive)
/// @return Range of antinode positions
[[nodiscard]] static auto generateAntinodeSequence(coordinate start, coordinate diff, int64_t max_x, int64_t max_y) {
    return std::views::iota(0) | std::views::transform([=](int64_t i) { return start + diff * i; }) |
           std::views::take_while([=](coordinate pos) { return pos.inBounds(max_x, max_y); });
}
} // namespace detail

/// @brief Finds discrete antinode positions between pairs of antennas
/// @param max_x_coordinate Maximum x coordinate (exclusive)
/// @param max_y_coordinate Maximum y coordinate (exclusive)
/// @param antenas Map of frequencies to antenna positions
/// @return Set of antinode positions
[[nodiscard]] auto findDiscreteAntinodes(int64_t max_x_coordinate, int64_t max_y_coordinate,
                                         std::multimap<char, coordinate> const & antenas)
    -> std::unordered_set<coordinate> {
    return std::views::transform(
               antenas,
               [&](auto const & antena) {
                   return detail::getOtherAntennaPositionsByFrequency(antena.first, antena.second, antenas) |
                          std::views::transform([&antena](coordinate const & other_coordinate) {
                              return other_coordinate + other_coordinate - antena.second;
                          }) |
                          std::views::filter([max_x_coordinate, max_y_coordinate](coordinate const & pos) {
                              return pos.inBounds(max_x_coordinate, max_y_coordinate);
                          });
               }) |
           std::views::join | aoc::ranges::to<std::unordered_set<coordinate>>;
}

/// @brief Finds continuous antinode positions along lines between antenna pairs
/// @param max_x_coordinate Maximum x coordinate (exclusive)
/// @param max_y_coordinate Maximum y coordinate (exclusive)
/// @param antenas Map of frequencies to antenna positions
/// @return Set of antinode positions
[[nodiscard]] auto findContinousAntinodes(int64_t max_x_coordinate, int64_t max_y_coordinate,
                                          std::multimap<char, coordinate> const & antenas)
    -> std::unordered_set<coordinate> {
    return std::views::transform(
               antenas,
               [&](auto const & antena) {
                   return detail::getOtherAntennaPositionsByFrequency(antena.first, antena.second, antenas) |
                          std::views::transform([&](coordinate const & other_coordinate) {
                              return detail::generateAntinodeSequence(other_coordinate,
                                                                      other_coordinate - antena.second,
                                                                      max_x_coordinate, max_y_coordinate);
                          }) |
                          std::views::join;
               }) |
           std::views::join | aoc::ranges::to<std::unordered_set<coordinate>>;
}

} // namespace aoc::day_8