
#include "file_ops.hpp"
#include <fstream>

auto readInput(std::string_view path) -> std::expected<std::string, std::error_code> {
    std::ifstream file(path.data(), std::ios::binary);
    if (!file) [[unlikely]] {
        return std::unexpected(std::make_error_code(std::errc::no_such_file_or_directory));
    }
    return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}