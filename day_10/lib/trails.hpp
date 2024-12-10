#pragma once

#include <cstdint>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "../../shared/src/vector2d.hpp"

namespace aoc::day_10 {

#define TRAIL_END   9
#define TRAIL_START 0

constexpr bool isTrailEnd(uint8_t value) {
    return value == TRAIL_END;
}

constexpr bool isTrailStart(uint8_t value) {
    return value == TRAIL_START;
}

struct tree_node {
    uint8_t value;
    std::vector<tree_node> children;
    aoc::math::Vector2D<uint8_t> position;
};

auto addEndpointIfReachable(std::unordered_set<aoc::math::Vector2D<uint8_t>> & uniqueEndPositions,
                            tree_node const & node) -> void;

void calculateNodeRating(size_t & rating, tree_node const & node);

struct trails {
    std::vector<tree_node> nodes;
    size_t calculateUniquePaths() const {
        auto counter = 0;
        for (auto root_node : nodes) {
            std::unordered_set<aoc::math::Vector2D<uint8_t>> uniqueEndPositions;
            addEndpointIfReachable(uniqueEndPositions, root_node);
            counter += uniqueEndPositions.size();
        }
        return counter;
    }

    size_t calculateRating() const {
        size_t ratingCounter = 0;
        for (auto root_node : nodes) {
            size_t currentRating = 0;
            calculateNodeRating(currentRating, root_node);
            ratingCounter += currentRating;
        }
        return ratingCounter;
    }
};

void calculateNodeRating(size_t & rating, tree_node const & node) {
    if (isTrailEnd(node.value)) {
        rating++;
    }
    for (auto child : node.children) {
        calculateNodeRating(rating, child);
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

} // namespace aoc::day_10