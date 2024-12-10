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

#include "../../shared/src/ranges_compatibility_layer.hpp"
#include "../../shared/src/vector2d.hpp"

namespace aoc::day_8 {

namespace detail {
/// @brief Gets positions of other antennas with the same frequency, excluding the specified position
/// @param frequency The frequency to match
/// @param exclude_pos The position to exclude from results
/// @param antenas Map of frequencies to antenna positions
/// @return Range of matching antenna positions
[[nodiscard]] static auto
getOtherAntennaPositionsByFrequency(char frequency, aoc::math::Vector2D<int64_t> const & exclude_pos,
                                    std::multimap<char, aoc::math::Vector2D<int64_t>> const & antenas) {
    auto range = antenas.equal_range(frequency);
    return std::ranges::subrange(range.first, range.second) |
           std::views::transform([](auto const & pair) { return pair.second; }) |
           std::views::filter([&exclude_pos](aoc::math::Vector2D<int64_t> const & pos) { return pos != exclude_pos; }) |
           std::views::common;
}

/// @brief Checks if the coordinate is within bounds
/// @param max_x Maximum x coordinate (exclusive)
/// @param max_y Maximum y coordinate (exclusive)
/// @return True if the coordinate is within bounds
[[nodiscard]] static auto inBounds(aoc::math::Vector2D<int64_t> vec, int64_t max_x, int64_t max_y) -> bool {
    return vec.y >= 0 && vec.y < max_y && vec.x >= 0 && vec.x < max_x;
}

/// @brief Generates a sequence of antinode positions along a line
/// @param start Starting position
/// @param diff Direction vector
/// @param max_x Maximum x coordinate (exclusive)
/// @param max_y Maximum y coordinate (exclusive)
/// @return Range of antinode positions
[[nodiscard]] static auto generateAntinodeSequence(aoc::math::Vector2D<int64_t> start,
                                                   aoc::math::Vector2D<int64_t> diff, int64_t max_x, int64_t max_y) {
    return std::views::iota(0) | std::views::transform([=](int64_t i) { return start + diff * i; }) |
           std::views::take_while(
               [=](aoc::math::Vector2D<int64_t> pos) { return detail::inBounds(pos, max_x, max_y); });
}
} // namespace detail

/// @brief Finds discrete antinode positions between pairs of antennas
/// @param max_x_coordinate Maximum x coordinate (exclusive)
/// @param max_y_coordinate Maximum y coordinate (exclusive)
/// @param antenas Map of frequencies to antenna positions
/// @return Set of antinode positions
[[nodiscard]] auto findDiscreteAntinodes(int64_t max_x_coordinate, int64_t max_y_coordinate,
                                         std::multimap<char, aoc::math::Vector2D<int64_t>> const & antenas)
    -> std::unordered_set<aoc::math::Vector2D<int64_t>> {
    return std::views::transform(
               antenas,
               [&](auto const & antena) {
                   return detail::getOtherAntennaPositionsByFrequency(antena.first, antena.second, antenas) |
                          std::views::transform([&antena](aoc::math::Vector2D<int64_t> const & other_coordinate) {
                              return other_coordinate + other_coordinate - antena.second;
                          }) |
                          std::views::filter(
                              [max_x_coordinate, max_y_coordinate](aoc::math::Vector2D<int64_t> const & pos) {
                                  return detail::inBounds(pos, max_x_coordinate, max_y_coordinate);
                              });
               }) |
           std::views::join | aoc::ranges::to<std::unordered_set<aoc::math::Vector2D<int64_t>>>;
}

/// @brief Finds continuous antinode positions along lines between antenna pairs
/// @param max_x_coordinate Maximum x coordinate (exclusive)
/// @param max_y_coordinate Maximum y coordinate (exclusive)
/// @param antenas Map of frequencies to antenna positions
/// @return Set of antinode positions
[[nodiscard]] auto findContinousAntinodes(int64_t max_x_coordinate, int64_t max_y_coordinate,
                                          std::multimap<char, aoc::math::Vector2D<int64_t>> const & antenas)
    -> std::unordered_set<aoc::math::Vector2D<int64_t>> {
    return std::views::transform(
               antenas,
               [&](auto const & antena) {
                   return detail::getOtherAntennaPositionsByFrequency(antena.first, antena.second, antenas) |
                          std::views::transform([&](aoc::math::Vector2D<int64_t> const & other_coordinate) {
                              return detail::generateAntinodeSequence(other_coordinate,
                                                                      other_coordinate - antena.second,
                                                                      max_x_coordinate, max_y_coordinate);
                          }) |
                          std::views::join;
               }) |
           std::views::join | aoc::ranges::to<std::unordered_set<aoc::math::Vector2D<int64_t>>>;
}

} // namespace aoc::day_8