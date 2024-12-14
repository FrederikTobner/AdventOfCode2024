#pragma once

#include <algorithm>
#include <cstdint>
#include <ranges>
#include <vector>

#include "robots.hpp"

namespace aoc::day_14 {

/// @brief Represents a world containing multiple robots and their interactions
struct world {
    /// @brief Constructs a new world with given robots and dimensions
    /// @param robots Vector of robots to populate the world
    /// @param x_size Width of the world
    /// @param y_size Height of the world
    world(std::vector<robot> robots, size_t x_size, size_t y_size);

    /// @brief Updates the position of all robots in the world
    auto update() -> void;

    /// @brief Calculates the safety score based on robot distribution in quadrants
    /// @return Product of the number of robots in each quadrant
    [[nodiscard]] auto safetyScore() const -> size_t;

    /// @brief Checks if robots form a valid Christmas tree pattern
    /// @return True if no robots overlap, false otherwise
    [[nodiscard]] auto formsChristmasTree() const -> bool;

  private:
    std::vector<robot> robots;
    size_t x_size;
    size_t y_size;

    /// @brief Checks if a robot is in the top-left quadrant
    [[nodiscard]] auto isInTopLeft(robot const & r) const -> bool;

    /// @brief Checks if a robot is in the top-right quadrant
    [[nodiscard]] auto isInTopRight(robot const & r) const -> bool;

    /// @brief Checks if a robot is in the bottom-left quadrant
    [[nodiscard]] auto isInBottomLeft(robot const & r) const -> bool;

    /// @brief Checks if a robot is in the bottom-right quadrant
    [[nodiscard]] auto isInBottomRight(robot const & r) const -> bool;
};

} // namespace aoc::day_14