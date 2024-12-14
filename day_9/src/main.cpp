#include <expected>
#include <map>
#include <ranges>
#include <string>
#include <string_view>
#include <system_error>
#include <unordered_set>
#include <vector>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

#include "../lib/check_sum_calculation.hpp"
#include "../lib/disk_map.hpp"
#include "../lib/disk_map_parser.hpp"

auto main(int argc, char const ** argv) -> int {
    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }

    auto lines = *input | std::views::split('\n') | std::views::transform([](auto && line) {
        auto sv = std::string_view(line.begin(), line.end());
        return sv.ends_with('\r') ? sv.substr(0, sv.size() - 1) : sv;
    }) | aoc::ranges::to<std::vector<std::string_view>>;

    if (lines.size() != 1) {
        std::println(stderr, "Expected a single line of input, got {}", lines.size());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    std::expected<aoc::day_9::disk_map, std::error_code> result = aoc::day_9::parseDiskMap(lines[0]);
    if (!result) {
        std::println(stderr, "Error parsing disk map: {}", result.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    aoc::day_9::disk_map parsed_disk_map = *result;

    // Part 1
    size_t part_1_checksum = aoc::day_9::calculateChecksumAfterCompacting(parsed_disk_map);

    std::println("Checksum after compacting: {}", part_1_checksum);

    // Part 2
    size_t part_2_checksum = aoc::day_9::calculateChecksumAfterCompactingLessAgressive(parsed_disk_map);

    std::println("Checksum after less aggressive compacting: {}", part_2_checksum);

    return aoc::EXIT_CODE_SUCCESS;
}
