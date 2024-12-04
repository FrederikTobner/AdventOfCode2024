#include <algorithm>
#include <ranges>

#include "../lib/lexer_rule.hpp"
#include "../lib/safety_check.hpp"

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/line_lexer.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

int main(int argc, char const * argv[]) {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::expected<std::vector<std::vector<uint8_t>>, std::error_code> parsed =
        aoc::lexer::linebased::tokenize<uint8_t>(*input, aoc::lexer::rules::handleToken);
    if (!parsed) [[unlikely]] {
        std::println(stderr, "Failed to parse input: {}", parsed.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    ptrdiff_t const safe_count =
        std::ranges::count_if(*parsed, [](auto const & line) { return safety_check::isSafe(line); });

    ptrdiff_t const fixable_count =
        std::ranges::count_if(*parsed, [](auto const & line) { return safety_check::canBeMadeSafe(line); });

    std::println("The number of safe levels is: {:#}", safe_count);
    std::println("The number of safe levels with one violation is: {:#}", fixable_count);

    return aoc::EXIT_CODE_SUCCESS;
}
