#include <expected>
#include <ranges>
#include <string>
#include <system_error>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/calculations.hpp"
#include "../lib/parser.hpp"
#include "../lib/warehouse.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    std::expected<std::pair<std::string_view, std::string_view>, std::error_code> split_input =
        aoc::day_15::parse_input(*input);
    if (!split_input) {
        std::println(stderr, "Failed to split input: {}", split_input.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto warehouse = aoc::day_15::parse_warehouse(split_input->first);
    auto moves = aoc::day_15::parse_movements(split_input->second);

    aoc::day_15::executeMoves(warehouse, moves);
    auto sum = aoc::day_15::calculate_gps_sum(warehouse);

    std::println("The sum of the gps coordinates is: {}", sum);

    return 0;
}
