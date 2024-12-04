#include <regex>

#include "../lib/calculations.hpp"
#include "../lib/pattern_matcher.hpp"

#include "../../shared/exit_code.hpp"
#include "../../shared/file_operations.hpp"
#include "../../shared/print_compatibility_layer.hpp"

int main(int argc, char const * argv[]) {

    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    uint64_t result = aoc::calculations::accumulateProducts(aoc::pattern_matcher::findMultiplicationPairs(*input));
    std::println("The result is: {:#}", result);

    uint64_t resultWithToggle =
        aoc::calculations::accumulateProducts(aoc::pattern_matcher::findMultiplicationPairsWithToggle(*input));
    std::println("The result is with the toggle is: {:#}", resultWithToggle);

    return aoc::EXIT_CODE_SUCCESS;
}