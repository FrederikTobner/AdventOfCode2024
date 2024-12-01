
#include "file_ops.hpp"
#include <fstream>

auto readInput(std::string_view path) -> std::optional<std::string> 
{
    if (std::ifstream file(path.data(), std::ios::binary); file) 
    {
        return std::string(std::istreambuf_iterator<char>(file),
                          std::istreambuf_iterator<char>());
    }
    return std::nullopt;
}