#include "word_search.hpp"

#include <array>

namespace aoc::day_4 {

namespace internal {
struct Direction {
    int dx;
    int dy;
};

static constexpr std::array<Direction, 8> DIRECTIONS{{
    {0, 1},  // right
    {1, 0},  // down
    {1, 1},  // diagonal down-right
    {1, -1}, // diagonal down-left
    {0, -1}, // left
    {-1, 0}, // up
    {-1, 1}, // diagonal up-right
    {-1, -1} // diagonal up-left
}};
} // namespace internal

auto findWord(std::span<std::string_view const> grid, std::string_view word) -> std::vector<match> {
    auto const rows = grid.size();
    auto const cols = grid.front().size();
    std::vector<match> matches;
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            for (auto [dx, dy] : internal::DIRECTIONS) {
                bool valid_match = true;
                std::vector<position> current_match;

                for (size_t i = 0; i < word.size() && valid_match; ++i) {
                    auto newRow = static_cast<int>(row) + i * dy;
                    auto newCol = static_cast<int>(col) + i * dx;

                    valid_match =
                        newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && grid[newRow][newCol] == word[i];

                    if (valid_match) {
                        current_match.push_back({static_cast<size_t>(newRow), static_cast<size_t>(newCol)});
                    }
                }

                if (valid_match && current_match.size() == word.size()) {
                    matches.push_back(match{std::move(current_match)});
                }
            }
        }
    }
    return matches;
}

} // namespace aoc::day_4