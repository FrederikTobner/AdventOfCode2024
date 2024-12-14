#pragma once

#include <algorithm>
#include <cstdint>
#include <ranges>
#include <vector>

#include "disk_map.hpp"


namespace aoc::day_9 {

/// @brief Calculates the checksum after compacting the disk map
/// @return The checksum
auto calculateChecksumAfterCompacting(disk_map const & disk_map) -> size_t;

/// @brief Calculates the checksum after compacting the disk map with a less aggressive strategy
/// @return The checksum
auto calculateChecksumAfterCompactingLessAgressive(disk_map const & disk_map) -> size_t;

} // namespace aoc::day_9
