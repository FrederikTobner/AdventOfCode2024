#pragma once
#include <optional>
#include <string>
#include <string_view>

/**
 * @brief Reads the entire contents of a file into a string
 * @param path Path to the file to read
 * @return std::optional<std::string> containing the file contents if successful, std::nullopt if the file couldn't be
 * opened
 * @throws std::runtime_error if file operations fail after opening
 */
[[nodiscard]] auto readInput(std::string_view path) -> std::optional<std::string>;