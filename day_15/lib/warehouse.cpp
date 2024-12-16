#include "warehouse.hpp"

#include <algorithm>
#include <cstdint>
#include <ranges>
#include <stdexcept>
#include <unordered_set>

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
            case cell_type::box_part_left:
                std::print("[");
                break;
            case cell_type::box_part_right:
                std::print("]");
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

struct BoxPairMove {
    aoc::math::vector_2d<int16_t> left;
    aoc::math::vector_2d<int16_t> right;
    aoc::math::vector_2d<int16_t> new_left;
    aoc::math::vector_2d<int16_t> new_right;
};

auto pushBoxPair(std::vector<std::vector<cell_type>> & warehouse, aoc::math::vector_2d<int16_t> const & box,
                 aoc::math::vector_2d<int16_t> const & other_box, aoc::math::vector_2d<int16_t> const & direction)
    -> bool {
    std::vector<BoxPairMove> moves;
    std::unordered_set<aoc::math::vector_2d<int16_t>> visited;

    std::vector<std::pair<aoc::math::vector_2d<int16_t>, aoc::math::vector_2d<int16_t>>> to_check;
    to_check.push_back({other_box, box});

    while (!to_check.empty()) {
        auto [left, right] = to_check.back();
        to_check.pop_back();

        if (visited.contains(left) || visited.contains(right)) {
            continue;
        }

        auto new_left = left + direction;
        auto new_right = right + direction;

        if (warehouse[new_left.y][new_left.x] == cell_type::wall ||
            warehouse[new_right.y][new_right.x] == cell_type::wall) {
            return false;
        }

        visited.insert(left);
        visited.insert(right);
        moves.push_back({left, right, new_left, new_right});

        if (warehouse[new_left.y][new_left.x] == cell_type::box_part_left) {
            to_check.push_back({new_left, new_left + aoc::math::vector_2d<int16_t>{1, 0}});
        }
        if (warehouse[new_right.y][new_right.x] == cell_type::box_part_left) {
            to_check.push_back({new_right, new_right + aoc::math::vector_2d<int16_t>{1, 0}});
        }
        if (warehouse[new_left.y][new_left.x] == cell_type::box_part_right) {
            to_check.push_back({new_left - aoc::math::vector_2d<int16_t>{1, 0}, new_left});
        }
        if (warehouse[new_right.y][new_right.x] == cell_type::box_part_right) {
            to_check.push_back({new_right - aoc::math::vector_2d<int16_t>{1, 0}, new_right});
        }
    }

    if (direction.y < 0) { // Moving up
        std::ranges::sort(moves, [](auto const & a, auto const & b) { return a.left.y < b.left.y; });
    } else if (direction.y > 0) { // Moving down
        std::ranges::sort(moves, [](auto const & a, auto const & b) { return a.left.y > b.left.y; });
    } else if (direction.x < 0) { // Moving left
        std::ranges::sort(moves, [](auto const & a, auto const & b) { return a.left.x < b.left.x; });
    } else if (direction.x > 0) { // Moving right
        std::ranges::sort(moves, [](auto const & a, auto const & b) { return a.left.x > b.left.x; });
    }

    for (auto const & move : moves) {
        warehouse[move.left.y][move.left.x] = cell_type::empty;
        warehouse[move.right.y][move.right.x] = cell_type::empty;
    }

    for (auto const & move : moves) {
        warehouse[move.new_left.y][move.new_left.x] = cell_type::box_part_left;
        warehouse[move.new_right.y][move.new_right.x] = cell_type::box_part_right;
    }

    return true;
}

// As the robot (@) attempts to move, if there are any boxes (O) in the way, the robot will also
// attempt to push those boxes. However, if this action would cause the robot or a box to move into a
// wall (#), nothing moves instead, including the robot)
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
    if (warehouse[new_position.y][new_position.x] == cell_type::box_part_left ||
        warehouse[new_position.y][new_position.x] == cell_type::box_part_right) {
        auto other_box_part = warehouse[new_position.y][new_position.x] == cell_type::box_part_left
                                  ? cell_type::box_part_right
                                  : cell_type::box_part_left;
        auto other_box_position = other_box_part == cell_type::box_part_right
                                      ? new_position + aoc::math::vector_2d<int16_t>{1, 0}
                                      : new_position + aoc::math::vector_2d<int16_t>{-1, 0};
        aoc::math::vector_2d<int16_t> new_box_position = new_position + direction;

        if (other_box_position.x > new_position.x || other_box_position.y > new_position.y) {
            if (!aoc::day_15::pushBoxPair(warehouse, other_box_position, new_position, direction)) {
                return;
            }
        } else {
            if (!aoc::day_15::pushBoxPair(warehouse, new_position, other_box_position, direction)) {
                return;
            }
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
        executeMove(warehouse, move, robot);
        // printWareHouse(warehouse);
    }
}

} // namespace aoc::day_15