/**
 * @file file_operations.cpp
 * @brief Implementation of file handling operations
 * @details Implements the file reading functionality declared in file_operations.hpp.
 * Handles file stream operations and error conditions.
 */

#include "file_operations.hpp"

#include <fstream>

auto aoc::fileops::readFromFile(std::string_view path) -> std::expected<std::string, std::error_code> {
    std::ifstream file(path.data(), std::ios::binary);
    if (!file) [[unlikely]] {
        return std::unexpected(std::make_error_code(std::errc::no_such_file_or_directory));
    }
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}