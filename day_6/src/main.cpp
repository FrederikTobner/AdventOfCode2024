#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include <algorithm>
#include <atomic>
#include <execution>
#include <numeric>
#include <span>
#include <string>

#include "../lib/puzzle_map.hpp"
#include "../lib/puzzle_map_formatter.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::vector<std::string_view> lines = aoc::day_4::processLines(*input);
    if (!aoc::day_4::validateGrid(lines)) {
        std::println(stderr, "Lines have different lengths");
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto const grid = std::span{lines};
    aoc::day_6::PuzzleMap map(grid);

    // Part 1
    while (!map.isGuardOutOfBounds()) {
        if (map.update()) {
            std::println("Player loop detected");
            break;
        }
    }
    std::println("Part 1: Visited positions: {:#}", map.getVisitedPositions().size());

    // Part 2
    auto freePositions = map.getFreePositions();

    auto result = std::transform_reduce(std::execution::par, freePositions.begin(), freePositions.end(), size_t{0},
                                        std::plus<>{}, [&map](auto const & position) {
                                            aoc::day_6::PuzzleMap mapCopy(map);
                                            mapCopy.insertObstacle(position);
                                            while (!mapCopy.isGuardOutOfBounds()) {
                                                if (mapCopy.update()) {
                                                    return size_t{1};
                                                }
                                            }
                                            return size_t{0};
                                        });

    std::println("Part 2: Amount of possible loops: {:#}", result);
    return 0;
}
