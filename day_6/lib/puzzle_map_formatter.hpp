#pragma once

#include <format>
#include <string>

#include "puzzle_map.hpp"

/// @brief Formatter for the PuzzleMap class
template <> struct std::formatter<aoc::day_6::PuzzleMap> : std::formatter<std::string_view> {
    [[nodiscard]] auto format(aoc::day_6::PuzzleMap map, format_context & ctx) const {
        return formatter<string_view>::format(map.toString(), ctx);
    }
};