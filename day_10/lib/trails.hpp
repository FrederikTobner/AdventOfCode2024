#pragma once

#include <cstdint>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

#include "../../shared/src/tree.hpp"
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

struct NodeData {
    uint8_t value;
    aoc::math::Vector2D<uint8_t> position;

    bool operator==(NodeData const & other) const {
        return value == other.value && position == other.position;
    }
};

struct trails {
    std::vector<aoc::tree::Node<NodeData>> nodes;

    size_t calculateUniquePaths() const {
        size_t uniquePathsCounter = 0;
        for (auto const & root_node : nodes) {
            std::unordered_set<aoc::math::Vector2D<uint8_t>> uniqueEndPositions;
            root_node.executeOnFullFillingCondition(
                [](NodeData const & data) { return isTrailEnd(data.value); },
                [&uniqueEndPositions](NodeData const & data) { uniqueEndPositions.insert(data.position); });
            uniquePathsCounter += uniqueEndPositions.size();
        }
        return uniquePathsCounter;
    }

    size_t calculateRating() const {
        size_t ratingCounter = 0;
        for (auto const & root_node : nodes) {
            ratingCounter +=
                root_node.countFullFillingCondition([](NodeData const & data) { return isTrailEnd(data.value); });
        }
        return ratingCounter;
    }
};

} // namespace aoc::day_10

namespace std {
template <> struct hash<aoc::day_10::NodeData> {
    auto operator()(aoc::day_10::NodeData const & data) const -> size_t {
        return hash<uint8_t>{}(data.value) ^ hash<aoc::math::Vector2D<uint8_t>>{}(data.position);
    }
};
} // namespace std