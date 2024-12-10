#pragma once

#include <cstdint>
#include <vector>

#include "trails.hpp"

namespace aoc::day_10 {

auto determineChildren(std::vector<std::vector<uint8_t>> const & map, uint8_t x, uint8_t y)
    -> std::vector<aoc::tree::Node<NodeData>> {
    std::vector<aoc::tree::Node<NodeData>> children;
    if (isTrailEnd(map[x][y])) {
        return children;
    }
    if (x > 0 && map[x - 1][y] == map[x][y] + 1) {
        auto position = aoc::math::Vector2D<uint8_t>{(uint8_t)(x - 1u), y};
        auto node_data = NodeData{map[x - 1][y], position};
        aoc::tree::Node<NodeData> node{node_data, determineChildren(map, x - 1u, y)};
        children.push_back(node);
    }
    if (x < map.size() - 1 && map[x + 1][y] == map[x][y] + 1) {
        auto position = aoc::math::Vector2D<uint8_t>{(uint8_t)(x + 1u), y};
        auto node_data = NodeData{map[x + 1][y], position};
        aoc::tree::Node<NodeData> node{node_data, determineChildren(map, x + 1, y)};
        children.push_back(node);
    }
    if (y > 0 && map[x][y - 1] == map[x][y] + 1u) {
        auto position = aoc::math::Vector2D<uint8_t>{x, (uint8_t)(y - 1u)};
        auto node_data = NodeData{map[x][y - 1], position};
        aoc::tree::Node<NodeData> node{node_data, determineChildren(map, x, y - 1)};
        children.push_back(node);
    }
    if (y < map[x].size() - 1 && map[x][y + 1] == map[x][y] + 1) {
        auto position = aoc::math::Vector2D<uint8_t>{x, (uint8_t)(y + 1u)};
        auto node_data = NodeData{map[x][y + 1], position};
        aoc::tree::Node<NodeData> node{node_data, determineChildren(map, x, y + 1)};
        children.push_back(node);
    }
    return children;
}

trails convertToTrails(std::vector<std::vector<uint8_t>> const & map) {
    std::vector<aoc::tree::Node<NodeData>> nodes;
    for (auto x : std::views::iota(uint8_t{0}, map.size())) {
        for (auto y : std::views::iota(uint8_t{0}, map[x].size())) {
            if (isTrailStart(map[x][y])) {
                auto children = determineChildren(map, x, y);
                auto position = aoc::math::Vector2D<uint8_t>{x, y};
                auto node_data = NodeData{map[x][y], position};
                aoc::tree::Node<NodeData> node{node_data, children};
                nodes.push_back(node);
            }
        }
    }
    return {nodes};
}

} // namespace aoc::day_10