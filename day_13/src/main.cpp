
#include <expected>
#include <ranges>
#include <string>
#include <system_error>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"
#include "../../shared/src/vector2d.hpp"

#include "../lib/calculations.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto lines = *input | std::views::split('\n') | std::views::transform([](auto && chars) {
        auto sv = std::string_view(chars.begin(), chars.end());
        if (sv.ends_with('\r')) {
            return sv.substr(0, sv.size() - 1);
        }
        return sv;
    }) | std::views::filter([](std::string_view sv) { return !sv.empty(); }) |
                 ::aoc::ranges::to<std::vector<std::string_view>>;

    size_t tokens_spent_part_1 = aoc::day_13::calculateTotalPrice(lines, 0);

    size_t tokens_spent_part_2 = aoc::day_13::calculateTotalPrice(lines, 10000000000000);

    std::println("Tokens spent part1={} part2={}", tokens_spent_part_1, tokens_spent_part_2);

    return aoc::EXIT_CODE_SUCCESS;
}
