#pragma once

#include <string>
#include <vector>

#include "../../shared/src/maze_cell.hpp"

namespace aoc::day_18 {

#define DIMENSIONS 71

struct maze {
    maze() {
        m_maze = std::vector<std::vector<aoc::path_finding::maze_cell>>(
            DIMENSIONS + 2,
            std::vector<aoc::path_finding::maze_cell>(DIMENSIONS + 2, aoc::path_finding::maze_cell::EMPTY));
        m_maze[1][DIMENSIONS] = aoc::path_finding::maze_cell::START;
        m_maze[DIMENSIONS][1] = aoc::path_finding::maze_cell::END;
        // Add walls to the borders
        for (size_t i = 0; i < DIMENSIONS + 2; ++i) {
            m_maze[0][i] = aoc::path_finding::maze_cell::WALL;
            m_maze[DIMENSIONS + 1][i] = aoc::path_finding::maze_cell::WALL;
            m_maze[i][0] = aoc::path_finding::maze_cell::WALL;
            m_maze[i][DIMENSIONS + 1] = aoc::path_finding::maze_cell::WALL;
        }
    }

    std ::string to_string() {
        std::string result;
        for (size_t y = 0; y < DIMENSIONS + 2; ++y) {
            for (size_t x = 0; x < DIMENSIONS + 2; ++x) {
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

    std::vector<std::vector<aoc::path_finding::maze_cell>> m_maze;
};

} // namespace aoc::day_18