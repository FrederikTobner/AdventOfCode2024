#include <expected>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

struct topographic_map {
    std::vector<std::vector<uint8_t>> topographies;
};

struct tree_node {
    uint8_t value;
    std::vector<tree_node> children;
    uint8_t x;
    uint8_t y;
};

struct position {
    uint8_t x;
    uint8_t y;

    auto operator==(position const & other) const -> bool {
        return x == other.x && y == other.y;
    }
};

namespace std {
template <> struct hash<position> {
    auto operator()(position const & p) const -> size_t {
        return std::hash<uint8_t>{}(p.x) ^ std::hash<uint8_t>{}(p.y);
    }
};
} // namespace std

struct trails {
    std::vector<tree_node> nodes;
};

auto determineChildren(topographic_map const & map, uint8_t x, uint8_t y) -> std::vector<tree_node> {
    std::vector<tree_node> children;
    if (map.topographies[x][y] == 9) {
        return children;
    }
    if (x > 0 && map.topographies[x - 1][y] == map.topographies[x][y] + 1) {
        tree_node node{map.topographies[x - 1][y], determineChildren(map, x - 1u, y), x - 1u, y};
        children.push_back(node);
    }
    if (x < map.topographies.size() - 1 && map.topographies[x + 1][y] == map.topographies[x][y] + 1) {
        tree_node node{map.topographies[x + 1][y], determineChildren(map, x + 1, y), x + 1u, y};
        children.push_back(node);
    }
    if (y > 0 && map.topographies[x][y - 1] == map.topographies[x][y] + 1u) {
        tree_node node{map.topographies[x][y - 1], determineChildren(map, x, y - 1), x, y - 1u};
        children.push_back(node);
    }
    if (y < map.topographies[x].size() - 1 && map.topographies[x][y + 1] == map.topographies[x][y] + 1) {
        tree_node node{map.topographies[x][y + 1], determineChildren(map, x, y + 1), x, y + 1u};
        children.push_back(node);
    }
    return children;
}

trails convert_to_trails(topographic_map const & map) {
    // Convert the topographic map to a tree of trails
    // In the topographic map it is possible to move in 4 directions: up, down, left, right. But only if the value is 1
    // greater than the current value. The tree of trails will represent all possible paths that can be taken accoring
    // to the topographic map The root nodes will be the ones with the value 0

    std::vector<tree_node> nodes;
    for (auto x : std::views::iota(uint8_t{0}, map.topographies.size())) {
        for (auto y : std::views::iota(uint8_t{0}, map.topographies[x].size())) {
            if (map.topographies[x][y] == 0) {
                auto children = determineChildren(map, x, y);
                tree_node node{map.topographies[x][y], children, x, y};
                nodes.push_back(node);
            }
        }
    }
    return {nodes};
}

auto addEndpointIfReachable(std::unordered_set<position> & uniqueEndPositions, tree_node const & node) -> void {
    if (node.children.empty() && node.value == 9) {
        uniqueEndPositions.insert({node.x, node.y});
    }
    for (auto child : node.children) {
        addEndpointIfReachable(uniqueEndPositions, child);
    }
}

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::vector<std::string_view> lines = aoc::grid_processor::processLines(*input);
    if (!aoc::grid_processor::validateGrid(lines)) {
        std::println(stderr, "Lines have different lengths");
        return aoc::EXIT_CODE_DATA_ERROR;
    }
    for (auto line : lines) {
        std::println("{}", line);
    }
    auto map = topographic_map{};
    for (auto line : lines) {
        std::vector<uint8_t> row;
        for (auto c : line) {
            row.push_back(c - '0');
        }
        map.topographies.push_back(row);
    }
    auto trails = convert_to_trails(map);
    auto counter = 0;
    // For every node in the tree, check if it has a depth of 10 - if true increase the counter
    for (auto root_node : trails.nodes) {
        std::unordered_set<position> uniqueEndPositions;
        addEndpointIfReachable(uniqueEndPositions, root_node);
        counter += uniqueEndPositions.size();
    }
    std::println("The number of unique paths is: {}", counter);

    return 0;
}
