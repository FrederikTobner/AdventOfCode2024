#pragma once

#include <cstdint>
#include <ranges>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

#include "../../shared/src/tree.hpp"
#include "../../shared/src/vector3d.hpp"

class TrailParserTest;

namespace aoc::day_10 {

/// Represents a collection of hiking trails and provides methods to analyze them
class trails {
    friend class ::TrailParserTest;

  public:
    /// Constructs a trails object from a collection of tree nodes
    /// @param nodes Vector of tree nodes representing the trail system
    trails(std::vector<aoc::tree::tree_node<aoc::math::vector_3d<uint8_t>>> nodes) : nodes(std::move(nodes)) {
    }

    /// Calculates the number of unique paths through the trail system
    /// @return The count of unique paths from start to end points
    [[nodiscard]] auto calculateUniquePaths() const -> size_t;

    /// Calculates the total rating of all possible paths through the trail system
    /// @return The sum of all valid path ratings
    [[nodiscard]] auto calculateRating() const -> size_t;

  private:
    std::vector<aoc::tree::tree_node<aoc::math::vector_3d<uint8_t>>> nodes;
};

/// Checks if a given trail value represents an end point
[[nodiscard]] auto isTrailEnd(uint8_t const & value) -> bool;

/// Checks if a given trail value represents a starting point
[[nodiscard]] auto isTrailStart(uint8_t const & value) -> bool;

} // namespace aoc::day_10