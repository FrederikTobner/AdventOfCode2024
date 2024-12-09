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

#include "../lib/disk_map.hpp"

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

    auto result = parseDiskMap(lines[0]);
    if (!result) {
        std::println(stderr, "Error parsing disk map: {}", result.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    auto part_1_map = *result;
    auto part_2_map = part_1_map;

    // Part 1
    auto part_1_checksum = part_1_map.calculateChecksumAfterCompacting();

    std::println("Checksum after compacting: {}", part_1_checksum);

    // Part 2
    auto part_2_checksum = part_2_map.calculateChecksumAfterCompactingLessAgressive();

    std::println("Checksum after less aggressive compacting: {}", part_2_checksum);

    return 0;
}
