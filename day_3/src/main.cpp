#include <regex>

#include "../lib/calculations.hpp"
#include "../lib/pattern_matcher.hpp"

#include "../../shared/exit_code.hpp"
#include "../../shared/file_operations.hpp"
#include "../../shared/print_compatibility_layer.hpp"

int main(int argc, char const * argv[]) {

    std::expected<std::string, std::error_code> input = fileops::readFromFile("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return EXIT_CODE_IO_ERROR;
    }

    auto matches = aoc::pattern_matcher::findMultiplicationPairsWithToggle(*input);
    for (auto const & match : matches) {
        std::println("Found numbers: ({}, {})", match.first, match.second);
    }

    uint64_t result = aoc::calculations::accumulateProducts(matches);
    std::println("The result is: {:#}", result);
    return 0;
}
