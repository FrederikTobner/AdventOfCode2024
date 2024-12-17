#include <expected>
#include <string>
#include <system_error>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"

#include "../lib/calculations.hpp"
#include "../lib/parser.hpp"
#include "../lib/virtual_machine.hpp"

auto main(int argc, char const ** argv) -> int {

    std::expected<std::string, std::error_code> input = aoc::file_operations::read("input.txt");
    if (!input) [[unlikely]] {
        std::println(stderr, "Could not open file: {}", input.error().message());
        return aoc::EXIT_CODE_IO_ERROR;
    }
    std::expected<aoc::day_17::program, std::error_code> program = aoc::day_17::parse_program(input.value());
    if (!program) [[unlikely]] {
        std::println(stderr, "Could not parse program: {}", program.error().message());
        return aoc::EXIT_CODE_DATA_ERROR;
    }

    std::vector<std::string> output_values;
    auto vm_out = [&output_values](std::string_view output) { output_values.push_back(std::string{output}); };

    auto vm = aoc::day_17::virtual_machine{vm_out};

    // Part 1
    vm.execute(*program);

    for (size_t i = 0; i < output_values.size(); ++i) {
        if (i != 0) {
            std::print(",{}", output_values[i]);
        } else {
            std::print("{}", output_values[i]);
        }
    }
    std::print("\n");

    // Part 2
    std::vector<int64_t> goals;
    for (int i = program->m_chunk.size() - 1; i >= 0; i--) {
        goals.push_back(static_cast<int64_t>(program->m_chunk[i]) % 8);
    }
    std::println("Register value of a to repplicate program in output {}",
                 aoc::day_17::findDesiredRegisterValue(0, goals, 0));

    return 0;
}
