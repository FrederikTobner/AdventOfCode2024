#pragma once

#include <vector>

#include "cell_type.hpp"

namespace aoc::day_15 {

/// @brief Transforms the warehouse to the format needed in part 2
/// @param warehouse The warehouse to transform
/// @return The transformed warehouse
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