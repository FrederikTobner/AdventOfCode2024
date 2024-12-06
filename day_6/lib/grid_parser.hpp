#pragma once

#include <expected>
#include <span>
#include <string_view>
#include <vector>

#include "facing_direction.hpp"
#include "tile_type.hpp"

namespace aoc::day_6 {

/// @brief Contains the parsed grid data including map layout and guard's initial state
/// @details Represents the complete initial state of the puzzle, including the grid layout
///          and the guard's starting position and orientation
struct ParsedGrid {
    /// @brief The 2D grid representation of the map
    std::vector<std::vector<TileType>> map;
    /// @brief The guard's initial position as {row, col}
    std::pair<int64_t, int64_t> guardPosition;
    /// @brief The guard's initial facing direction
    FacingDirection guardDirection;
};

/// @brief Converts a character representation of direction to FacingDirection enum
/// @param c The character to convert ('^', 'v', '<', '>')
/// @return The corresponding FacingDirection
/// @details Optimized using platform-specific implementations:
///          - MSVC: Uses switch with __assume(0)
///          - GCC/Clang: Uses computed goto for better performance
[[nodiscard]] constexpr auto charToGuardDirection(char c) -> FacingDirection {
#ifdef _MSC_VER
    switch (c) {
    case '^':
        return FacingDirection::Up;
    case 'v':
        return FacingDirection::Down;
    case '<':
        return FacingDirection::Left;
    case '>':
        return FacingDirection::Right;
    default:
        __assume(0); // Unreachable
    }
#else // Use Computed goto's for GCC and Clang
    static void * const jumpTable[] = {&&up, &&down, &&left, &&right};
    goto * jumpTable[c - '^'];

up:
    return FacingDirection::Up;
down:
    return FacingDirection::Down;
left:
    return FacingDirection::Left;
right:
    return FacingDirection::Right;
#endif
}

/// @brief Checks if a character represents a guard
/// @param c The character to check
/// @return true if the character is '^', 'v', '<', or '>'
[[nodiscard]] constexpr auto isGuard(char c) -> bool {
    return c == '^' || c == 'v' || c == '<' || c == '>';
}

/// @brief Parses a grid of characters into a structured representation
/// @param grid The input grid as a span of string_views
/// @return A ParsedGrid if successful, or an error message if parsing fails
/// @details Validates the following conditions:
///          - Exactly one guard must be present
///          - All characters must be valid tile types
///          - Grid must not be empty
[[nodiscard]] auto parseGrid(std::span<std::string_view const> grid) -> std::expected<ParsedGrid, std::string> {
    ParsedGrid result;
    result.map.reserve(grid.size());
    bool guardFound = false;

    for (size_t rowIdx = 0; rowIdx < grid.size(); ++rowIdx) {
        auto const & row = grid[rowIdx];
        std::vector<TileType> rowTiles;
        rowTiles.reserve(row.size());

        for (size_t colIdx = 0; colIdx < row.size(); ++colIdx) {
            auto const tile = row[colIdx];
            if (isGuard(tile)) {
                if (guardFound) {
                    return std::unexpected("Multiple guards found in grid");
                }
                guardFound = true;
                rowTiles.push_back(TileType::Guard);
                result.guardPosition = {rowIdx, colIdx};
                result.guardDirection = charToGuardDirection(tile);
                continue;
            }

            switch (tile) {
            case '.':
                rowTiles.push_back(TileType::Empty);
                break;
            case '#':
                rowTiles.push_back(TileType::Obstacle);
                break;
            default:
                return std::unexpected("Invalid tile type");
            }
        }
        result.map.push_back(std::move(rowTiles));
    }

    if (!guardFound) {
        return std::unexpected("No guard found in grid");
    }

    return result;
}

} // namespace aoc::day_6