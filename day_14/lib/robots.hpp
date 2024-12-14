#pragma once

#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>

#include "../../shared/src/vector2d.hpp"

#include "../../shared/src/parsing_rules.hpp"

namespace aoc::day_14 {

/// @brief Represents a robot with position and velocity in a 2D space
struct robot {
    /// @brief Current position of the robot
    aoc::math::vector_2d<int16_t> position;
    /// @brief Current velocity of the robot
    aoc::math::vector_2d<int16_t> velocity;

    /// @brief Updates the robot's position based on its velocity and world boundaries
    /// @param x_size The width of the world
    /// @param y_size The height of the world
    auto update(size_t x_size, size_t y_size) -> void;
};

/// @brief Parses a robot configuration from a text line
/// @param line String view containing the robot configuration in format "p=x,y v=dx,dy"
/// @return Expected containing either a robot or an error code
[[nodiscard]] auto parseRobot(std::string_view line) -> std::expected<robot, std::error_code>;

} // namespace aoc::day_14
