/**
 * @file file_operations.hpp
 * @brief File handling operations interface
 * @details Declares functions for reading input files safely with error handling.
 * Provides abstractions over standard file operations with modern C++ features.
 */

#pragma once

#include <expected>
#include <string>
#include <string_view>
#include <system_error>

namespace fileops {

/**
 * @brief Reads the entire contents of a file into a string
 * @param path Path to the file to read
 * @return std::optional<std::string> containing the file contents if successful, std::nullopt if the file couldn't be
 * opened
 * @throws std::runtime_error if file operations fail after opening
 */
[[nodiscard]] auto readFromFile(std::string_view path) -> std::expected<std::string, std::error_code>;

} // namespace fileops