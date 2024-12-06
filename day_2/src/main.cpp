#include <algorithm>
#include <expected>
#include <ranges>

#include "../lib/safety_check.hpp"

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/line_splitter.hpp"
#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::expected<std::vector<std::vector<uint8_t>>, std::error_code> parsed = aoc::splitter::linebased::split<uint8_t>(
        *input, aoc::parser::rules::parse_number<uint8_t>, std::execution::par_unseq);
    if (!parsed) [[unlikely]] {
        std::println(stderr, "Failed to parse input: {}", parsed.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    ptrdiff_t const safe_count =
        std::ranges::count_if(*parsed, [](auto const & line) { return aoc::day_2::isSafe(line); });

    ptrdiff_t const fixable_count =
        std::ranges::count_if(*parsed, [](auto const & line) { return aoc::day_2::canBeMadeSafe(line); });

    std::println("The number of safe levels is: {:#}", safe_count);
    std::println("The number of safe levels with one violation is: {:#}", fixable_count);

    return aoc::EXIT_CODE_SUCCESS;
}
