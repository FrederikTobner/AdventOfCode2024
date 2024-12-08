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
[[nodiscard]] static auto getOtherAntennaPositionsByFrequency(char frequency, coordinate const & exclude_pos,
                                                              std::multimap<char, coordinate> const & antenas) {
    auto range = antenas.equal_range(frequency);
    return std::ranges::subrange(range.first, range.second) |
           std::views::transform([](auto const & pair) { return pair.second; }) |
           std::views::filter([&exclude_pos](coordinate const & pos) { return pos != exclude_pos; }) |
           std::views::common;
}

[[nodiscard]] static auto generateAntinodeSequence(coordinate start, coordinate diff, int64_t max_x, int64_t max_y) {
    return std::views::iota(0) | std::views::transform([=](int64_t i) { return start + diff * i; }) |
           std::views::take_while([=](coordinate pos) { return pos.inBounds(max_x, max_y); });
}
} // namespace detail

[[nodiscard]] auto determineAntinodes(int64_t max_x_coordinate, int64_t max_y_coordinate,
                                      std::multimap<char, coordinate> const & antenas)
    -> std::unordered_set<coordinate> {
    return std::views::transform(
               antenas,
               [&](auto const & entry) {
                   return detail::getOtherAntennaPositionsByFrequency(entry.first, entry.second, antenas) |
                          std::views::transform([&entry](coordinate const & other_pos) {
                              coordinate diff = other_pos - entry.second;
                              return other_pos + diff;
                          }) |
                          std::views::filter([max_x_coordinate, max_y_coordinate](coordinate const & pos) {
                              return pos.inBounds(max_x_coordinate, max_y_coordinate);
                          });
               }) |
           std::views::join | aoc::ranges::to<std::unordered_set<coordinate>>;
}

[[nodiscard]] auto determineAntinodes2(int64_t max_x_coordinate, int64_t max_y_coordinate,
                                       std::multimap<char, coordinate> const & antenas)
    -> std::unordered_set<coordinate> {
    return std::views::transform(
               antenas,
               [max_x = max_x_coordinate, max_y = max_y_coordinate, antenas = antenas](auto const & entry) {
                   return detail::getOtherAntennaPositionsByFrequency(entry.first, entry.second, antenas) |
                          std::views::transform([start = entry.second, max_x, max_y](coordinate const & other_pos) {
                              return detail::generateAntinodeSequence(other_pos, other_pos - start, max_x, max_y);
                          }) |
                          std::views::join;
               }) |
           std::views::join | aoc::ranges::to<std::unordered_set<coordinate>>;
}

} // namespace aoc::day_8