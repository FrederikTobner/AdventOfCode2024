#include "exit_code.hpp"
#include "file_ops.hpp"
#include "parser.hpp"
#include "printer.hpp"

#include <algorithm>
#include <numeric>
#include <optional>
#include <ranges>

auto main(int argc, char const ** argv) -> int {
    auto input = readInput("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return EXIT_CODE_IO_ERROR;
    }

    // Use ranges::to for cleaner container creation
    auto [leftList, rightList] = parseInput(*input);

    if (leftList.size() != rightList.size()) {
        std::println(stderr, "The lists are not of equal size");
        return EXIT_CODE_DATA_ERROR;
    }

    // Part 1 - Calculate the total distance
    uint64_t totalDistance =
        std::transform_reduce(leftList.begin(), leftList.end(), rightList.begin(), std::uint64_t{0}, std::plus<>{},
                              [](auto a, auto b) { return std::abs(a - b); });

    std::println("The totalDistance is: {}", totalDistance);

    // Part 2 - Calculate a similarity score
    uint64_t similarityScore = std::ranges::fold_left(
        leftList | std::views::transform([&rightList](auto const & num) { return rightList.count(num) * num; }),
        std::uint64_t{0}, std::plus<>{});

    std::println("The similarity score is: {}", similarityScore);

    return EXIT_CODE_SUCCESS;
}