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
    uint8_t original_file_length;
};

struct disk_map {
    std::vector<disk_map_entry> entries;

    size_t calculateChecksumAfterCompacting() {
        size_t checksum = 0;
        size_t counter = 0;
        auto entries_copy = entries;
        for (size_t fileIndex = 0; fileIndex < entries_copy.size(); ++fileIndex) {
            auto [file_length, free_space, original_file_length] = entries_copy[fileIndex];
            for (size_t i = 0; i < file_length; ++i) {
                checksum += counter * fileIndex;
                counter++;
            }
            for (size_t i = 0; i < free_space; ++i) {
                for (size_t indexFromEnd = entries.size() - 1; indexFromEnd > fileIndex; --indexFromEnd) {
                    auto [file_length, free_space, original_file_length] = entries_copy[indexFromEnd];
                    if (file_length > 0) {
                        entries_copy[indexFromEnd].file_length--;
                        checksum += counter * (indexFromEnd);
                        entries_copy[fileIndex].free_space--;
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
        auto entries_copy = entries;
        size_t max_end_index = entries.size() - 1;
        for (size_t fileIndex = 0; fileIndex < entries.size(); ++fileIndex) {
            auto [file_length, free_space, original_file_length] = entries_copy[fileIndex];
            for (size_t i = 0; i < file_length; ++i) {
                checksum += counter * fileIndex;
                counter++;
            }
            if (file_length < original_file_length) {
                counter += original_file_length - file_length;
            }
            for (size_t i = 0; i < free_space; ++i) {
                // Get the last disk map entry that has still a file_length > 0. Start seartching from the back / end
                for (size_t indexFromEnd = max_end_index; indexFromEnd > fileIndex; --indexFromEnd) {
                    auto [file_length, free_space, original_file_length] = entries_copy[indexFromEnd];
                    if (file_length > 0 &&
                        (entries_copy[indexFromEnd].file_length <= entries_copy[fileIndex].free_space)) {
                        entries_copy[indexFromEnd].file_length--;
                        checksum += counter * (indexFromEnd);
                        entries_copy[fileIndex].free_space--;
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
            result.entries.push_back({*file_length, 0, *file_length});
        } else {
            auto free_space = aoc::parser::rules::parse_number<uint8_t>(input.substr(index + 1, 1));
            if (!free_space) {
                return std::unexpected(free_space.error());
            }
            result.entries.push_back({*file_length, *free_space, *file_length});
        }
    }

    return result;
}
