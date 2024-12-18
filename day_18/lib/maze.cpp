#include "maze.hpp"

#include <ranges>
#include <string>
#include <vector>

#include "../../shared/src/maze_cell.hpp"

namespace aoc::day_18 {

#define DIMENSIONS 71

maze::maze() {
    m_maze = std::vector<std::vector<aoc::path_finding::maze_cell>>(
        DIMENSIONS, std::vector<aoc::path_finding::maze_cell>(DIMENSIONS, aoc::path_finding::maze_cell::EMPTY));
    m_maze[0][0] = aoc::path_finding::maze_cell::START;
    m_maze[DIMENSIONS - 1][DIMENSIONS - 1] = aoc::path_finding::maze_cell::END;
}

std ::string maze::to_string() {
    std::string result;
    for (size_t y = 0; y < DIMENSIONS; ++y) {
        for (size_t x = 0; x < DIMENSIONS; ++x) {
            switch (m_maze[x][y]) {
            case aoc::path_finding::maze_cell::EMPTY:
                result += ".";
                break;
            case aoc::path_finding::maze_cell::WALL:
                result += "#";
                break;
            case aoc::path_finding::maze_cell::START:
                result += "S";
                break;
            case aoc::path_finding::maze_cell::END:
                result += "E";
                break;
            }
        }
        result += "\n";
    }
    return result;
}

auto buildMaze(std::vector<std::vector<int16_t>> const & coordinates, size_t limit) -> maze {
    auto result = maze{};
    for (auto const & [x, y] : coordinates | std::views::take(limit) | std::views::transform([](auto const & line) {
                                   return std::pair{line[0], line[1]};
                               })) {
        result.m_maze[x][y] = aoc::path_finding::maze_cell::WALL;
    }
    return result;
}

} // namespace aoc::day_18