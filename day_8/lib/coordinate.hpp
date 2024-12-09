#pragma once

#include <cstddef>
#include <memory>

namespace aoc::day_8 {

/// @brief Represents a 2D coordinate with y (row) and x (column) components
struct coordinate {
    int64_t y; ///< The y (row) coordinate
    int64_t x; ///< The x (column) coordinate

    /// @brief Inequality comparison operator
    /// @param other The coordinate to compare with
    /// @return True if coordinates are not equal
    auto operator!=(coordinate const & other) const -> bool {
        return y != other.y || x != other.x;
    }

    /// @brief Equality comparison operator
    /// @param other The coordinate to compare with
    /// @return True if coordinates are equal
    auto operator==(coordinate const & other) const -> bool {
        return y == other.y && x == other.x;
    }

    /// @brief Subtraction operator
    /// @param other The coordinate to subtract
    /// @return A new coordinate representing the difference
    [[nodiscard]] auto operator-(coordinate const & other) const -> coordinate {
        return {y - other.y, x - other.x};
    }

    /// @brief Addition operator
    /// @param other The coordinate to add
    /// @return A new coordinate representing the sum
    [[nodiscard]] auto operator+(coordinate const & other) const -> coordinate {
        return {y + other.y, x + other.x};
    }

    /// @brief Scalar multiplication operator
    /// @param scalar The scalar value to multiply by
    /// @return A new coordinate scaled by the given factor
    auto operator*(int64_t scalar) const -> coordinate {
        return {y * scalar, x * scalar};
    }

    /// @brief Addition assignment operator
    /// @param other The coordinate to add to this one
    /// @return Reference to this coordinate after addition
    auto operator+=(coordinate const & other) -> coordinate & {
        y += other.y;
        x += other.x;
        return *this;
    }

    /// @brief Checks if the coordinate is within bounds
    /// @param max_x Maximum x coordinate (exclusive)
    /// @param max_y Maximum y coordinate (exclusive)
    /// @return True if the coordinate is within bounds
    [[nodiscard]] auto inBounds(int64_t max_x, int64_t max_y) const -> bool {
        return y >= 0 && y < max_y && x >= 0 && x < max_x;
    }
};

} // namespace aoc::day_8
namespace std {

/// @brief Hash specialization for VisitedPosition to enable use in unordered containers
template <> struct hash<aoc::day_8::coordinate> {
    /// @brief Combines the hashes of row, column and direction into a single hash value
    /// @param position The position to hash
    /// @return A hash value representing the complete state of the position
    [[nodiscard]] auto operator()(aoc::day_8::coordinate const position) const -> std::size_t {
        return std::hash<int64_t>{}(position.y) ^ std::hash<int64_t>{}(position.x);
    }
};
} // namespace std