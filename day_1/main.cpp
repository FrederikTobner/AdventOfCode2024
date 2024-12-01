#include "file_ops.hpp"
#include "parser.hpp"
#include <iostream>
#include <numeric>

auto main(int argc, char const *argv[]) -> int 
{
    auto input = readInput("input.txt");
    if (!input) {
        std::cerr << "Could not open file\n";
        return 1;
    }

    auto [set1, set2] = parseInput(*input);
    
    if (set1.size() != set2.size()) {
        throw std::runtime_error("The two sets are not the same size");
    }

    auto result = std::transform_reduce(
        set1.begin(), set1.end(),
        set2.begin(),
        std::uint64_t{0},
        std::plus<>{},
        [](auto a, auto b) { return std::abs(a - b); }
    );

    std::cout << "The result is: " << result << '\n';
    return 0;
}