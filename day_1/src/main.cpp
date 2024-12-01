/**
 * @file main.cpp
 * @brief Main program entry point
 * @details Coordinates the overall program flow, including file reading,
 * input parsing, calculations, and result output. Handles error conditions
 * and provides appropriate exit codes.
 */

#include "../../shared/exit_code.hpp"
#include "../../shared/print_compatibility_layer.hpp"
#include "../lib/calculations.hpp"
#include "../lib/file_operations.hpp"
#include "../lib/parser.hpp"


auto main(int argc, char const ** argv) -> int {
    auto input = readInput("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return EXIT_CODE_IO_ERROR;
    }

    auto parsed = parser::parseInput(*input); // Add namespace qualification
    if (!parsed) [[unlikely]] {
        std::println(stderr, "Failed to parse input: {}", parsed.error().message());
        return EXIT_CODE_DATA_ERROR;
    }

    auto const & [leftList, rightList] = *parsed;

    if (leftList.size() != rightList.size()) [[unlikely]] {
        std::println(stderr, "Lists have different sizes: {} vs {}", leftList.size(),
                     rightList.size()); // Simplified format string
        return EXIT_CODE_DATA_ERROR;
    }

    auto totalDistance = calculateTotalDistance(leftList, rightList);
    std::println("The totalDistance is: {:#}", totalDistance);

    auto similarityScore = calculateSimilarityScore(leftList, rightList);
    std::println("The similarity score is: {:#}", similarityScore);

    return EXIT_CODE_SUCCESS;
}