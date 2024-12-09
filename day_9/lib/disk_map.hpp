#pragma once

#include <cstdint>
#include <exception>
#include <expected>
#include <string_view>
#include <system_error>
#include <vector>

#include "../../shared/src/parsing_rules.hpp"

struct disk_map_entry {
    uint8_t file_length;
    uint8_t free_space;
};

struct disk_map_internal_entry {
    uint8_t file_length;
    uint8_t free_space;
    uint8_t original_file_length;
};

struct disk_map {
    std::vector<disk_map_entry> entries;

    size_t calculateChecksumAfterCompacting() {
        size_t checksum = 0;
        size_t counter = 0;
        auto entries_copy = entries;
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

    size_t calculateChecksumAfterCompactingLessAgressive() {
        size_t checksum = 0;
        size_t counter = 0;
        auto entries_copy = entries | std::views::transform([](auto const & entry) {
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
                // Get the last disk map entry that has still a file_length > 0. Start seartching from the back / end
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
};

std::expected<disk_map, std::error_code> parseDiskMap(std::string_view input) {
    disk_map result;
    // If the input does not have an even size return an error
    size_t size = input.size();
    for (size_t index = 0; index < size; index += 2) {
        auto file_length = aoc::parser::rules::parse_number<uint8_t>(input.substr(index, 1));
        if (!file_length) {
            return std::unexpected(file_length.error());
        }
        auto free_space = 0;
        if (index + 1 == size) {
            result.entries.push_back({*file_length, 0});
        } else {
            auto free_space = aoc::parser::rules::parse_number<uint8_t>(input.substr(index + 1, 1));
            if (!free_space) {
                return std::unexpected(free_space.error());
            }
            result.entries.push_back({*file_length, *free_space});
        }
    }

    return result;
}
