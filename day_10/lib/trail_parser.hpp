#pragma once

#include <cstdint>
#include <vector>

#include "trails.hpp"

namespace aoc::day_10 {

auto determineChildren(std::vector<std::vector<uint8_t>> const & map, uint8_t x, uint8_t y) -> std::vector<tree_node> {
    std::vector<tree_node> children;
    if (isTrailEnd(map[x][y])) {
        return children;
    }
    if (x > 0 && map[x - 1][y] == map[x][y] + 1) {
        auto position = aoc::math::Vector2D<uint8_t>{(uint8_t)(x - 1u), y};
        tree_node node{map[x - 1][y], determineChildren(map, x - 1u, y), position};
        children.push_back(node);
    }
    if (x < map.size() - 1 && map[x + 1][y] == map[x][y] + 1) {
        auto position = aoc::math::Vector2D<uint8_t>{(uint8_t)(x + 1u), y};
        tree_node node{map[x + 1][y], determineChildren(map, x + 1, y), position};
        children.push_back(node);
    }
    if (y > 0 && map[x][y - 1] == map[x][y] + 1u) {
        auto position = aoc::math::Vector2D<uint8_t>{x, (uint8_t)(y - 1u)};
        tree_node node{map[x][y - 1], determineChildren(map, x, y - 1), position};
        children.push_back(node);
    }
    if (y < map[x].size() - 1 && map[x][y + 1] == map[x][y] + 1) {
        auto position = aoc::math::Vector2D<uint8_t>{x, (uint8_t)(y + 1u)};
        tree_node node{map[x][y + 1], determineChildren(map, x, y + 1), position};
        children.push_back(node);
    }
    return children;
}

trails convertToTrails(std::vector<std::vector<uint8_t>> const & map) {
    std::vector<tree_node> nodes;
    for (auto x : std::views::iota(uint8_t{0}, map.size())) {
        for (auto y : std::views::iota(uint8_t{0}, map[x].size())) {
            if (isTrailStart(map[x][y])) {
                auto children = determineChildren(map, x, y);
                auto position = aoc::math::Vector2D<uint8_t>{x, y};
                tree_node node{map[x][y], children, position};
                nodes.push_back(node);
            }
        }
    }
    return {nodes};
}

} // namespace aoc::day_10