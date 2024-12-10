#pragma once

#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "../../shared/src/vector2d.hpp"

#define TRAIL_END   9
#define TRAIL_START 0

constexpr bool isTrailEnd(uint8_t value) {
    return value == TRAIL_END;
}

constexpr bool isTrailStart(uint8_t value) {
    return value == TRAIL_START;
}

struct topographic_map {
    std::vector<std::vector<uint8_t>> topographies;
};

struct tree_node {
    uint8_t value;
    std::vector<tree_node> children;
    aoc::math::Vector2D<uint8_t> position;
};

struct trails {
    std::vector<tree_node> nodes;
};

auto determineChildren(topographic_map const & map, uint8_t x, uint8_t y) -> std::vector<tree_node> {
    std::vector<tree_node> children;
    if (isTrailEnd(map.topographies[x][y])) {
        return children;
    }
    if (x > 0 && map.topographies[x - 1][y] == map.topographies[x][y] + 1) {
        auto position = aoc::math::Vector2D<uint8_t>{(uint8_t)(x - 1u), y};
        tree_node node{map.topographies[x - 1][y], determineChildren(map, x - 1u, y), position};
        children.push_back(node);
    }
    if (x < map.topographies.size() - 1 && map.topographies[x + 1][y] == map.topographies[x][y] + 1) {
        auto position = aoc::math::Vector2D<uint8_t>{(uint8_t)(x + 1u), y};
        tree_node node{map.topographies[x + 1][y], determineChildren(map, x + 1, y), position};
        children.push_back(node);
    }
    if (y > 0 && map.topographies[x][y - 1] == map.topographies[x][y] + 1u) {
        auto position = aoc::math::Vector2D<uint8_t>{x, (uint8_t)(y - 1u)};
        tree_node node{map.topographies[x][y - 1], determineChildren(map, x, y - 1), position};
        children.push_back(node);
    }
    if (y < map.topographies[x].size() - 1 && map.topographies[x][y + 1] == map.topographies[x][y] + 1) {
        auto position = aoc::math::Vector2D<uint8_t>{x, (uint8_t)(y + 1u)};
        tree_node node{map.topographies[x][y + 1], determineChildren(map, x, y + 1), position};
        children.push_back(node);
    }
    return children;
}

trails convertToTrails(topographic_map const & map) {
    std::vector<tree_node> nodes;
    for (auto x : std::views::iota(uint8_t{0}, map.topographies.size())) {
        for (auto y : std::views::iota(uint8_t{0}, map.topographies[x].size())) {
            if (isTrailStart(map.topographies[x][y])) {
                auto children = determineChildren(map, x, y);
                auto position = aoc::math::Vector2D<uint8_t>{x, y};
                tree_node node{map.topographies[x][y], children, position};
                nodes.push_back(node);
            }
        }
    }
    return {nodes};
}

void calculateRating(size_t & rating, tree_node const & node) {
    if (isTrailEnd(node.value)) {
        rating++;
    }
    for (auto child : node.children) {
        calculateRating(rating, child);
    }
}

auto addEndpointIfReachable(std::unordered_set<aoc::math::Vector2D<uint8_t>> & uniqueEndPositions,
                            tree_node const & node) -> void {
    if (isTrailEnd(node.value)) {
        uniqueEndPositions.insert({node.position.x, node.position.y});
    }
    for (auto child : node.children) {
        addEndpointIfReachable(uniqueEndPositions, child);
    }
}