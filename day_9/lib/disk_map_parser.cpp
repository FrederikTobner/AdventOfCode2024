#include "disk_map_parser.hpp"

#include "../../shared/src/parsing_rules.hpp"

namespace aoc::day_9 {
/// @brief Parses a disk map from a string
/// @param input The input string to parse
/// @return The parsed disk map or an error code
auto parseDiskMap(std::string_view input) -> std::expected<disk_map, std::error_code> {
    disk_map result;
    size_t size = input.size();
    for (size_t index = 0; index < size; index += 2) {
        auto file_length = aoc::parser::rules::parse_number<uint8_t>(input.substr(index, 1));
        if (!file_length) {
            return std::unexpected(file_length.error());
        }
        uint8_t free_space = 0;
        if (index + 1 != size) {
            auto free_space_parsed = aoc::parser::rules::parse_number<uint8_t>(input.substr(index + 1, 1));
            if (!free_space_parsed) {
                return std::unexpected(free_space_parsed.error());
            }
            free_space = *free_space_parsed;
        }
        result.entries.push_back({*file_length, free_space});
    }

    return result;
}

} // namespace aoc::day_9