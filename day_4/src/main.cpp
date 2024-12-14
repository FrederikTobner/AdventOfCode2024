#include <span>
#include <string>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/grid_processor.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/match_filter.hpp"
#include "../lib/word_search.hpp"

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

    std::vector<aoc::day_4::match> xmas_matches = aoc::day_4::findWord(lines, "XMAS");
    std::println("Found {:#} XMAS matches:", xmas_matches.size());

    std::vector<aoc::day_4::match> mas_matches = aoc::day_4::findWord(lines, "MAS");
    ptrdiff_t sum = aoc::day_4::countOverlappingDiagonal(mas_matches);
    std::println("Found {:#} X-MAS matches", sum);

    return aoc::EXIT_CODE_SUCCESS;
}
