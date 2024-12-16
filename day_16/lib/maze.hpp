#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "maze_cell.hpp"

namespace aoc::day_16 {
auto parseMaze(std::vector<std::string_view> lines) -> std::vector<std::vector<maze_cell>> {
    std::vector<std::vector<maze_cell>> maze;
    for (auto const & line : lines) {
        std::vector<maze_cell> row;
        for (auto const & cell : line) {
            switch (cell) {
            case '#':
                row.push_back(maze_cell::WALL);
                break;
            case '.':
                row.push_back(maze_cell::EMPTY);
                break;
            case 'S':
                row.push_back(maze_cell::START);
                break;
            case 'E':
                row.push_back(maze_cell::END);
                break;
            default:
                throw std::invalid_argument("Invalid cell type in maze");
            }
        }
        maze.push_back(row);
    }
    return maze;
}

} // namespace aoc::day_16