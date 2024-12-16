#include "warehouse.hpp"

#include <cstdint>
#include <stdexcept>

#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/vector2d.hpp"

namespace aoc::day_15 {

auto printWareHouse(std::vector<std::vector<cell_type>> & warehouse) -> void {
    for (auto const & row : warehouse) {
        for (auto const & cell : row) {
            switch (cell) {
            case cell_type::empty:
                std::print(".");
                break;
            case cell_type::wall:
                std::print("#");
                break;
            case cell_type::box:
                std::print("O");
                break;
            case cell_type::robot:
                std::print("@");
                break;
            }
        }
        std::println("");
    }
}

auto pushBox(std::vector<std::vector<cell_type>> & warehouse, aoc::math::vector_2d<int16_t> const & box,
             aoc::math::vector_2d<int16_t> const & direction) -> bool {
    auto new_position = box + direction;
    if (warehouse[new_position.y][new_position.x] == cell_type::wall) {
        return false;
    } else if (warehouse[new_position.y][new_position.x] == cell_type::box) {
        // Check if we can push the next box as well using recursion
        if (!pushBox(warehouse, new_position, direction)) {
            return false;
        }
    }
    warehouse[new_position.y][new_position.x] = cell_type::box;
    warehouse[box.y][box.x] = cell_type::empty;
    return true;
}

// As the robot (@) attempts to move, if there are any boxes (O) in the way, the robot will also attempt to push
// those boxes. However, if this action would cause the robot or a box to move into a wall (#), nothing moves
// instead, including the robot)
static auto executeMove(std::vector<std::vector<cell_type>> & warehouse, aoc::math::Direction const & move,
                        aoc::math::vector_2d<int16_t> & robot) -> void {
    auto direction = aoc::math::getDirectionVector(move);
    aoc::math::vector_2d<int16_t> new_position = robot + direction;
    if (warehouse[new_position.y][new_position.x] == cell_type::wall) {
        return;
    }
    if (warehouse[new_position.y][new_position.x] == cell_type::box) {
        aoc::math::vector_2d<int16_t> new_box_position = new_position + direction;
        if (!aoc::day_15::pushBox(warehouse, new_position, direction)) {
            return;
        }
    }
    warehouse[new_position.y][new_position.x] = cell_type::robot;
    warehouse[robot.y][robot.x] = cell_type::empty;
    robot = new_position;
}

auto executeMoves(std::vector<std::vector<cell_type>> & warehouse, std::vector<aoc::math::Direction> const & moves)
    -> void {
    size_t robot_x = SIZE_MAX;
    size_t robot_y = SIZE_MAX;

    // Look for the robot in the warehouse
    for (size_t y = 0; y < warehouse.size(); ++y) {
        for (size_t x = 0; x < warehouse[y].size(); ++x) {
            if (warehouse[y][x] == cell_type::robot) {
                if (robot_x != SIZE_MAX || robot_y != SIZE_MAX) {
                    throw std::invalid_argument("Multiple robots found in warehouse");
                }
                robot_x = x;
                robot_y = y;
                break;
            }
        }
    }

    if (robot_x == SIZE_MAX || robot_y == SIZE_MAX) {
        throw std::invalid_argument("No robot found in warehouse");
    }

    if (robot_x > INT16_MAX || robot_y > INT16_MAX) {
        throw std::invalid_argument("Robot position out of bounds");
    }

    auto robot = aoc::math::vector_2d<int16_t>{static_cast<int16_t>(robot_x), static_cast<int16_t>(robot_y)};

    for (auto const & move : moves) {
        // printWareHouse(warehouse);
        executeMove(warehouse, move, robot);
    }
}

} // namespace aoc::day_15