#pragma once

#include <cstdint>
#include <exception>

#include <string_view>
#include <vector>

namespace aoc::day_9 {

/// @brief Represents a disk map entry
struct disk_map_entry {
    uint8_t file_length;
    uint8_t free_space;
};

/// @brief Represents a disk map entry with additional information for internal processing
struct disk_map_internal_entry {
    uint8_t file_length;
    uint8_t free_space;
    uint8_t original_file_length;
};

/// @brief Represents a disk map
struct disk_map {
    /// @brief The entries in the disk map
    std::vector<disk_map_entry> entries;
};

} // namespace aoc::day_9
