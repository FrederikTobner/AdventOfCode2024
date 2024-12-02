#include "../lib/parser.hpp"
#include "../lib/safety_check.hpp"

#include "../../shared/exit_code.hpp"
#include "../../shared/file_operations.hpp"
#include "../../shared/print_compatibility_layer.hpp"

int main(int argc, char const * argv[]) {
    std::expected<std::string, std::error_code> input = fileops::readFromFile("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return EXIT_CODE_IO_ERROR;
    }

    std::expected<std::vector<std::vector<uint8_t>>, std::error_code> parsed = parser::parseInput(*input);
    if (!parsed) [[unlikely]] {
        std::println(stderr, "Failed to parse input: {}", parsed.error().message());
        return EXIT_CODE_DATA_ERROR;
    }
    size_t counter = 0;
    for (auto const & line : *parsed) {
        if (safety_check::isSafe(line)) {
            counter++;
        }
    }
    std::println("The number of safe levels is: {:#}", counter);

    size_t counter2 = 0;
    for (auto const & line : *parsed) {
        if (safety_check::canBeMadeSafe(line)) {
            counter2++;
        }
    }

    std::println("The number of safe levels with one violation is: {:#}", counter2);

    return 0;
}
