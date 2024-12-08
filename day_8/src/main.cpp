#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <execution>
#include <map>
#include <ranges>
#include <string>
#include <unordered_set>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/antinodes.hpp"
#include "../lib/coordinate.hpp"
#include "../lib/map_renderer.hpp"

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

    int64_t max_y_coordinate = lines.size();
    int64_t max_x_coordinate = lines[0].size();

    std::multimap<char, aoc::day_8::coordinate> antenas;
    for (auto x : std::views::iota(int64_t{0}, max_y_coordinate)) {
        for (auto y : std::views::iota(int64_t{0}, max_x_coordinate)) {
            if (std::isalnum(lines[x][y])) {
                antenas.insert({lines[x][y], {x, y}});
            }
        }
    }

    // Part 1
    std::unordered_set<aoc::day_8::coordinate> antinodes =
        aoc::day_8::findDiscreteAntinodes(max_x_coordinate, max_y_coordinate, antenas);

    aoc::day_8::renderResult(lines, antinodes, max_x_coordinate, max_y_coordinate);

    // Part 2
    std::unordered_set<aoc::day_8::coordinate> antinodes2 =
        aoc::day_8::findContinousAntinodes(max_x_coordinate, max_y_coordinate, antenas);

    aoc::day_8::renderResult(lines, antinodes2, max_x_coordinate, max_y_coordinate);

    return 0;
}
