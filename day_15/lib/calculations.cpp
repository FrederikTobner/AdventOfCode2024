#include "calculations.hpp"

namespace aoc::day_15 {

/// @brief Calculates the gps coordinate of a box
/// @param box The box to calculate the gps coordinate for
/// @return The gps coordinate of the box
auto calculate_gps_coordinate(aoc::math::vector_2d<size_t> const & box) -> size_t {
    return box.y * 100 + box.x;
}

/// @brief Calculates the sum of the gps coordinates of all boxes in the warehouse
/// @param warehouse The warehouse to calculate the sum for
/// @return The sum of the gps coordinates of all boxes in the warehouse
auto calculate_gps_sum(std::vector<std::vector<cell_type>> & warehouse) -> size_t {
    size_t sum = 0;
    for (size_t y = 0; y < warehouse.size(); ++y) {
        for (size_t x = 0; x < warehouse[y].size(); ++x) {
            if (warehouse[y][x] == cell_type::BOX) {
                sum += calculate_gps_coordinate({x, y});
            } else if (warehouse[y][x] == cell_type::BOX_PART_LEFT) {
                sum += calculate_gps_coordinate({x, y});
            }
        }
    }

    return sum;
}

} // namespace aoc::day_15