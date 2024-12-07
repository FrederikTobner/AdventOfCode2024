/**
 * @file main.cpp
 * @brief Main program entry point
 * @details Coordinates the overall program flow, including file reading,
 * input parsing, calculations, and result output. Handles error conditions
 * and provides appropriate exit codes.
 */

#include <cstdint>
#include <expected>
#include <string>

#include "../lib/calculations.hpp"

#include "../../shared/src/column_splitter.hpp"
#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto tokens = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>(
        *input, aoc::parser::rules::parse_number<int64_t>, std::execution::par);
    if (!tokens) [[unlikely]] {
        std::println(stderr, "Failed to parse input: {}", tokens.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto const & [leftList, rightList] = *tokens;

    if (leftList.size() != rightList.size()) [[unlikely]] {
        std::println(stderr, "Lists have different sizes: {} vs {}", leftList.size(), rightList.size());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    uint64_t totalDistance = aoc::day_1::totalDistance(leftList, rightList);
    uint64_t similarityScore = aoc::day_1::similarityScore(leftList, rightList);

    std::println("The totalDistance is: {:#}", totalDistance);
    std::println("The similarity score is: {:#}", similarityScore);

    return aoc::EXIT_CODE_SUCCESS;
}