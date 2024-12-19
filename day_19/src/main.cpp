#include <expected>
#include <string>
#include <system_error>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/matcher.hpp"
#include "../lib/parser.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }
    std::println("Input: {}", *input);

    auto parsed_input = aoc::day_19::parseInput(*input);
    if (!parsed_input) [[unlikely]] {
        std::println(stderr, "Could not parse input: {}", parsed_input.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    size_t solvable = 0;
    auto matcher = aoc::day_19::pattern_matcher(parsed_input->patterns);
    for (auto const & design : parsed_input->designs) {
        auto result = matcher.can_construct(design);
        if (result) {
            solvable++;
            std::println("Solvable design: {}", design);
        }
    }
    std::println("Solvable designs: {}", solvable);

    return 0;
}
