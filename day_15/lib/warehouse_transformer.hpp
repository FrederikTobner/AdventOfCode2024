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
            case cell_type::empty:
                transformed_row.push_back(cell_type::empty);
                transformed_row.push_back(cell_type::empty);
                break;
            case cell_type::wall:
                transformed_row.push_back(cell_type::wall);
                transformed_row.push_back(cell_type::wall);
                break;
            case cell_type::box:
                transformed_row.push_back(cell_type::box_part_left);
                transformed_row.push_back(cell_type::box_part_right);
                break;
            case cell_type::robot:
                transformed_row.push_back(cell_type::robot);
                transformed_row.push_back(cell_type::empty);
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