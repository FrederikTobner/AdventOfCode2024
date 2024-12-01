#include "file_ops.hpp"
#include "parser.hpp"
#include "printer.hpp"
#include <numeric>

auto main(int argc, char const * argv[]) -> int {
    std::optional<std::string> input = readInput("input.txt");
    if (!input) {
        std::println(stderr, "Could not open file");
        return 1;
    }

    auto [leftList, rightList] = parseInput(*input);

    if (leftList.size() != rightList.size()) {
        throw std::runtime_error("The two sets are not the same size");
    }

    uint64_t result = std::transform_reduce(leftList.begin(), leftList.end(), rightList.begin(), std::uint64_t{0},
                                            std::plus<>{}, [](auto a, auto b) { return std::abs(a - b); });

    std::println("The result is: {}", result);
    return 0;
}