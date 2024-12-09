#pragma once

#include <cstdint>
#include <expected>
#include <string_view>
#include <system_error>


#include "disk_map.hpp"

namespace aoc::day_9 {
/// @brief Parses a disk map from a string
/// @param input The input string to parse
/// @return The parsed disk map or an error code
auto parseDiskMap(std::string_view input) -> std::expected<disk_map, std::error_code>;

} // namespace aoc::day_9