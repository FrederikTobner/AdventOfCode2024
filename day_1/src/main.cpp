/**
 * @file main.cpp
 * @brief Main program entry point
 * @details Coordinates the overall program flow, including file reading,
 * input parsing, calculations, and result output. Handles error conditions
 * and provides appropriate exit codes.
 */

#include "../lib/calculations.hpp"
#include "../lib/lexer_rule.hpp"

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/multiset_column_lexer.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto tokens = aoc::lexer::columnbased::tokenize<int64_t, 2>(*input, aoc::lexer::rules::numberProducer);
    if (!tokens) [[unlikely]] {
        std::println(stderr, "Failed to parse input: {}", tokens.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto const & [leftList, rightList] = *tokens; // array destructuring still works

    if (leftList.size() != rightList.size()) [[unlikely]] {
        std::println(stderr, "Lists have different sizes: {} vs {}", leftList.size(), rightList.size());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    uint64_t totalDistance = calculations::totalDistance(leftList, rightList);
    uint64_t similarityScore = calculations::similarityScore(leftList, rightList);

    std::println("The totalDistance is: {:#}", totalDistance);
    std::println("The similarity score is: {:#}", similarityScore);

    return aoc::EXIT_CODE_SUCCESS;
}