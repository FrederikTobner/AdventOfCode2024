/**
 * @file main.cpp
 * @brief Main program entry point
 * @details Coordinates the overall program flow, including file reading,
 * input parsing, calculations, and result output. Handles error conditions
 * and provides appropriate exit codes.
 */

#include "../lib/calculations.hpp"
#include "../lib/file_operations.hpp"
#include "../lib/parser.hpp"

#include "../../shared/exit_code.hpp"
#include "../../shared/print_compatibility_layer.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = fileops::readFromFile("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return EXIT_CODE_IO_ERROR;
    }

    std::expected<std::pair<std::multiset<int64_t>, std::multiset<int64_t>>, std::error_code> parsed =
        parser::parseInput(*input);
    if (!parsed) [[unlikely]] {
        std::println(stderr, "Failed to parse input: {}", parsed.error().message());
        return EXIT_CODE_DATA_ERROR;
    }

    auto const & [leftList, rightList] = *parsed;

    if (leftList.size() != rightList.size()) [[unlikely]] {
        std::println(stderr, "Lists have different sizes: {} vs {}", leftList.size(), rightList.size());
        return EXIT_CODE_DATA_ERROR;
    }

    uint64_t totalDistance = calculations::totalDistance(leftList, rightList);
    std::println("The totalDistance is: {:#}", totalDistance);

    uint64_t similarityScore = calculations::similarityScore(leftList, rightList);
    std::println("The similarity score is: {:#}", similarityScore);

    return EXIT_CODE_SUCCESS;
}