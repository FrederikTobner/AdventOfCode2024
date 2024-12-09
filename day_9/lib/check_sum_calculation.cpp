#include "check_sum_calculation.hpp"

namespace aoc::day_9 {

auto calculateChecksumAfterCompacting(disk_map const & disk_map) -> size_t {
    size_t checksum = 0;
    size_t counter = 0;
    auto entries_copy = disk_map.entries;
    for (size_t fileIndex = 0; fileIndex < entries_copy.size(); ++fileIndex) {
        auto & entry_to_process = entries_copy[fileIndex];
        for (size_t i = 0; i < entry_to_process.file_length; ++i) {
            checksum += counter * fileIndex;
            counter++;
        }
        uint8_t original_free_space = entry_to_process.free_space;
        for (size_t i = 0; i < original_free_space; ++i) {
            for (size_t indexFromEnd = entries_copy.size() - 1; indexFromEnd > fileIndex; --indexFromEnd) {
                auto & entry_to_move = entries_copy[indexFromEnd];
                if (entry_to_move.file_length > 0) {
                    entry_to_move.file_length--;
                    checksum += counter * (indexFromEnd);
                    entry_to_process.free_space--;
                    counter++;
                    break;
                }
            }
        }
    }

    return checksum;
}

/// @brief Calculates the checksum after compacting the disk map with a less aggressive strategy
/// @return The checksum
auto calculateChecksumAfterCompactingLessAgressive(disk_map const & disk_map) -> size_t {
    size_t checksum = 0;
    size_t counter = 0;
    auto entries_copy = disk_map.entries | std::views::transform([](auto const & entry) {
                            return disk_map_internal_entry{entry.file_length, entry.free_space, entry.file_length};
                        }) |
                        aoc::ranges::to<std::vector<disk_map_internal_entry>>;
    for (size_t fileIndex = 0; fileIndex < entries_copy.size(); ++fileIndex) {
        auto & entry_to_process = entries_copy[fileIndex];
        for (size_t i = 0; i < entry_to_process.file_length; ++i) {
            checksum += counter * fileIndex;
            counter++;
        }
        if (entry_to_process.file_length < entry_to_process.original_file_length) {
            counter += entry_to_process.original_file_length - entry_to_process.file_length;
        }
        uint8_t original_free_space = entry_to_process.free_space;
        for (size_t i = 0; i < original_free_space; ++i) {
            for (size_t indexFromEnd = entries_copy.size() - 1; indexFromEnd > fileIndex; --indexFromEnd) {
                auto & entry_to_move = entries_copy[indexFromEnd];
                if (entry_to_move.file_length > 0 && (entry_to_move.file_length <= entry_to_process.free_space)) {
                    entry_to_move.file_length--;
                    checksum += counter * (indexFromEnd);
                    entry_to_process.free_space--;
                    break;
                }
            }
            counter++;
        }
    }

    return checksum;
}

} // namespace aoc::day_9