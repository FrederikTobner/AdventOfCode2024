#include "calculations.hpp"
#include "exit_code.hpp"
#include "file_operations.hpp"
#include "parser.hpp"
#include "print_compatibility_layer.hpp"

auto main(int argc, char const ** argv) -> int {
    auto input = readInput("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return EXIT_CODE_IO_ERROR;
    }

    auto parsed = parseInput(*input);
    if (!parsed) [[unlikely]] {
        std::println(stderr, "Failed to parse input: {}", parsed.error().message());
        return EXIT_CODE_DATA_ERROR;
    }

    auto & [leftList, rightList] = *parsed;

    if (leftList.size() != rightList.size()) [[unlikely]] {
        std::println(stderr, "The lists are not of equal size: leftList.size={}, rightList.size={}", leftList.size(),
                     rightList.size());
        return EXIT_CODE_DATA_ERROR;
    }

    auto totalDistance = calculateTotalDistance(leftList, rightList);
    std::println("The totalDistance is: {:#}", totalDistance);

    auto similarityScore = calculateSimilarityScore(leftList, rightList);
    std::println("The similarity score is: {:#}", similarityScore);

    return EXIT_CODE_SUCCESS;
}