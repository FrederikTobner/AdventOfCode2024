#include <span>
#include <string>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/grid_processor.hpp"
#include "../lib/match_filter.hpp"
#include "../lib/word_search.hpp"

auto main(int argc, char const ** argv) -> int {
    auto input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto lines = aoc::grid_processor::processLines(*input);
    if (!aoc::grid_processor::validateGrid(lines)) {
        std::println(stderr, "Lines have different lengths");
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto const grid = std::span{lines};
    auto xmas_matches = aoc::word_search::findWord(grid, "XMAS");
    std::println("Found {:#} XMAS matches:", xmas_matches.size());

    auto mas_matches = aoc::word_search::findWord(grid, "MAS");
    auto sum = aoc::match_filter::countOverlappingDiagonal(mas_matches);
    std::println("Found {:#} X-MAS matches", sum);

    return 0;
}
