#include "trail_parser.hpp"

namespace aoc::day_10 {

static auto determineChildren(std::vector<std::vector<uint8_t>> const & map, aoc::math::vector_3d<uint8_t> const & pos)
    -> std::vector<aoc::tree::tree_node<aoc::math::vector_3d<uint8_t>>> {
    if (isTrailEnd(map[pos.x][pos.y])) {
        return {};
    }

    static constexpr std::array<Direction, 4> directions = {Direction::UP, Direction::RIGHT, Direction::DOWN,
                                                            Direction::LEFT};

    std::vector<aoc::tree::tree_node<aoc::math::vector_3d<uint8_t>>> children;
    uint8_t current_value = map[pos.x][pos.y];
    uint8_t expected_next_value = current_value + 1;

    for (auto dir : directions) {
        auto new_pos = calculateNewPosition(pos, dir);
        if (!isValidPosition(new_pos, map)) {
            continue;
        }

        if (map[new_pos.x][new_pos.y] == expected_next_value) {
            auto child_position = aoc::math::vector_3d<uint8_t>{new_pos.x, new_pos.y, map[new_pos.x][new_pos.y]};
            children.push_back(createNode(child_position, determineChildren(map, child_position)));
        }
    }

    return children;
}

auto convertToTrails(std::vector<std::vector<uint8_t>> const & map) -> trails {
    std::vector<aoc::tree::tree_node<aoc::math::vector_3d<uint8_t>>> nodes;

    for (auto x : std::views::iota(uint8_t{0}, static_cast<uint8_t>(map.size()))) {
        for (auto y : std::views::iota(uint8_t{0}, static_cast<uint8_t>(map[x].size()))) {
            if (isTrailStart(map[x][y])) {
                auto position = aoc::math::vector_3d<uint8_t>{x, y, map[x][y]};
                nodes.push_back(createNode(position, determineChildren(map, position)));
            }
        }
    }

    return {nodes};
}

} // namespace aoc::day_10