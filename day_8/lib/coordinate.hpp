#pragma once

#include <cstddef>
#include <memory>

namespace aoc::day_8 {

struct coordinate {
    int64_t y;
    int64_t x;

    auto operator!=(coordinate const & other) const -> bool {
        return y != other.y || x != other.x;
    }

    auto operator==(coordinate const & other) const -> bool {
        return y == other.y && x == other.x;
    }

    [[nodiscard]] auto operator-(coordinate const & other) const -> coordinate {
        return {y - other.y, x - other.x};
    }

    [[nodiscard]] auto operator+(coordinate const & other) const -> coordinate {
        return {y + other.y, x + other.x};
    }

    auto operator+=(coordinate const & other) -> coordinate & {
        y += other.y;
        x += other.x;
        return *this;
    }

    [[nodiscard]] auto in_bounds(int64_t max_x, int64_t max_y) const -> bool {
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