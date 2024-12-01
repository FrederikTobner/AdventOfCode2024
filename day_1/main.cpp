#include "exit_code.hpp"
#include "file_ops.hpp"
#include "parser.hpp"
#include "printer.hpp"

#include <algorithm>
#include <execution>
#include <numeric>
#include <ranges>
#include <vector>

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

    // Part 1 - Calculate the total distance
    auto distances = std::ranges::zip_view(leftList, rightList) | std::views::transform([](auto pair) {
                         auto [a, b] = pair;
                         return std::abs(a - b);
                     }) |
                     std::ranges::to<std::vector>();

    auto totalDistance = std::reduce(std::execution::par, distances.begin(), distances.end(), std::uint64_t{0});

    std::println("The totalDistance is: {:#}", totalDistance);

    // Part 2 - Calculate a similarity score
    auto similarities = leftList |
                        std::views::transform([&rightList](auto const & num) { return rightList.count(num) * num; }) |
                        std::ranges::to<std::vector>();

    auto similarityScore = std::reduce(std::execution::par, similarities.begin(), similarities.end(), std::uint64_t{0});

    std::println("The similarity score is: {:#}", similarityScore);

    return EXIT_CODE_SUCCESS;
}