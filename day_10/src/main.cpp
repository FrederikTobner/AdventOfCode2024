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

#include "../lib/trails.hpp"

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

    auto map = topographic_map{};
    for (auto line : lines) {
        std::vector<uint8_t> row;
        for (auto c : line) {
            row.push_back(c - '0');
        }
        map.topographies.push_back(row);
    }
    auto trails = convertToTrails(map);
    auto counter = 0;

    // Part 1
    for (auto root_node : trails.nodes) {
        std::unordered_set<aoc::math::Vector2D<uint8_t>> uniqueEndPositions;
        addEndpointIfReachable(uniqueEndPositions, root_node);
        counter += uniqueEndPositions.size();
    }
    std::println("The number of unique paths is: {}", counter);

    // Part 2
    size_t ratingCounter = 0;
    for (auto root_node : trails.nodes) {
        size_t currentRating = 0;
        calculateRating(currentRating, root_node);
        ratingCounter += currentRating;
    }

    std::println("The total rating of all trails is: {}", ratingCounter);

    return 0;
}
