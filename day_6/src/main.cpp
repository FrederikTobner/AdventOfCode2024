#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include <algorithm>
#include <atomic>
#include <execution>
#include <numeric>
#include <string>

#include "../lib/grid_parser.hpp"
#include "../lib/puzzle_map.hpp"

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

    auto parsedGrid = aoc::day_6::parseGrid(lines);
    if (!parsedGrid) {
        std::println(stderr, "Failed to parse grid: {}", parsedGrid.error());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    aoc::day_6::PuzzleMap map(parsedGrid->map, parsedGrid->guardPosition, parsedGrid->guardDirection);

    // Part 1
    while (!map.isGuardOutOfBounds()) {
        if (!map.update()) {
            std::println("Player loop detected");
            break;
        }
    }

    auto visitedPositionsFiltered = std::set<std::pair<size_t, size_t>>{};
    for (auto const & position : map.getVisitedPositions()) {
        visitedPositionsFiltered.insert({position.row, position.col});
    }
    std::println("Part 1: Visited positions: {:#}", visitedPositionsFiltered.size());

    // Part 2
    aoc::day_6::PuzzleMap map2(parsedGrid->map, parsedGrid->guardPosition, parsedGrid->guardDirection);

    auto result =
        std::transform_reduce(std::execution::par, visitedPositionsFiltered.begin(), visitedPositionsFiltered.end(),
                              size_t{0}, std::plus<>{}, [&map2](auto const & position) {
                                  aoc::day_6::PuzzleMap mapCopy(map2);
                                  mapCopy.insertObstacle(position);
                                  while (!mapCopy.isGuardOutOfBounds()) {
                                      if (!mapCopy.update()) {
                                          return size_t{1};
                                      }
                                  }
                                  return size_t{0};
                              });

    std::println("Part 2: Amount of possible loops: {:#}", result);
    return 0;
}
