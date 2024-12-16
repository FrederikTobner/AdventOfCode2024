#pragma once

#include <vector>

#include "cell_type.hpp"

namespace aoc::day_15 {

// Transforms the given warehouse using the following rules:
//    If the tile is #, the new map contains ## instead.
//   If the tile is O, the new map contains [] instead.
//   If the tile is ., the new map contains .. instead.
//   If the tile is @, the new map contains @. instead.
auto transformWarehouse(std::vector<std::vector<cell_type>> & warehouse) -> std::vector<std::vector<cell_type>> {
    auto transformed_warehouse = std::vector<std::vector<cell_type>>{};
    for (auto const & row : warehouse) {
        auto transformed_row = std::vector<cell_type>{};
        for (auto const & cell : row) {
            switch (cell) {
            case cell_type::EMPTY:
                transformed_row.push_back(cell_type::EMPTY);
                transformed_row.push_back(cell_type::EMPTY);
                break;
            case cell_type::WALL:
                transformed_row.push_back(cell_type::WALL);
                transformed_row.push_back(cell_type::WALL);
                break;
            case cell_type::BOX:
                transformed_row.push_back(cell_type::BOX_PART_LEFT);
                transformed_row.push_back(cell_type::BOX_PART_RIGHT);
                break;
            case cell_type::ROBOT:
                transformed_row.push_back(cell_type::ROBOT);
                transformed_row.push_back(cell_type::EMPTY);
                break;
            default:
                break;
            }
        }
        transformed_warehouse.push_back(transformed_row);
    }
    return transformed_warehouse;
}

} // namespace aoc::day_15