
#include <expected>
#include <string>
#include <system_error>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/parser.hpp"
#include "../lib/plant_location.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto parsedInput = aoc::day_12::parseInput(*input);
    if (!parsedInput) {
        std::println(stderr, "Error parsing input: {}", parsedInput.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }
    auto gardenGroupMap = *parsedInput;

    auto totalCost = 0;
    auto totalCost_part2 = 0;
    for (auto const & [group, locations] : gardenGroupMap) {
        size_t fenceCost = 0;
        size_t sides = 0;
        auto const groups = aoc::day_12::splitIntoConnectedLocations(locations);
        for (auto const & group : groups) {
            fenceCost += aoc::day_12::calculateFencePrice(group);
            sides += aoc::day_12::calculateFencePrice2(group);
        }
        std::println("Group: {} has fenceCost of {} for part 1 and {} for part 2", group, fenceCost, sides);
        totalCost += fenceCost;
        totalCost_part2 += sides;
    }

    std::println("Total cost part 1: {}", totalCost);
    std::println("Total cost part 2: {}", totalCost_part2);

    return aoc::EXIT_CODE_SUCCESS;
}
