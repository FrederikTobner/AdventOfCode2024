#include <algorithm>
#include <expected>
#include <string>
#include <system_error>

#include "../../shared/src/exit_code.hpp"
#include "../../shared/src/file_operations.hpp"
#include "../../shared/src/print_compatibility_layer.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

#include "../lib/generated.hpp"
#include "../lib/parser.hpp"
#include "../lib/transpiler.hpp"
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

    if (argc == 2) {
        auto arg = std::string_view{argv[0]};
        if (arg == "--extract") {
            std::println("Transpiled program:\n{}", aoc::day_17::extract_helpers(program->m_chunk));
            return aoc::EXIT_CODE_SUCCESS;
        } else if (arg == "--opcode") {
            std::println("Opcode program:\n{}", program->m_chunk.to_string());
            return aoc::EXIT_CODE_SUCCESS;
        } else if (arg == "--transpile") {
            std::println("Transpiled program:\n{}", aoc::day_17::transpile(*program));
            return aoc::EXIT_CODE_SUCCESS;
        } else if (arg == "--help") {
            std::println(R"(Help:
            --extract: Extracts the helper functions from the program
            --opcode: Prints the program as opcodes
            --transpile: Transpiles the program to C++
            --help: Prints this help message)");
            return aoc::EXIT_CODE_SUCCESS;
        } else if (arg == "--run") {
            std::vector<std::string> output_values;
            auto vm_out = [&output_values](std::string_view output) { output_values.push_back(std::string{output}); };
            auto vm = aoc::day_17::virtual_machine{vm_out};
            vm.execute(*program);
            for (size_t i = 0; i < output_values.size(); ++i) {
                if (i != 0) {
                    std::print(",{}", output_values[i]);
                } else {
                    std::print("{}", output_values[i]);
                }
            }
            std::print("\n");
            return aoc::EXIT_CODE_SUCCESS;
        } else {
            std::println("Usage: {} [--extract | --opcode | --transpile | --help]", arg);
            return aoc::EXIT_CODE_DATA_ERROR;
        }
    }

    // Part 1
    aoc::day_17::run_using_best_lang();

    // Part 2
    std::vector<int64_t> goals;
    for (int i = program->m_chunk.size() - 1; i >= 0; i--) {
        goals.push_back(static_cast<int64_t>(program->m_chunk[i]) % 8);
    }
    std::println("Register value to replicate program in output {}", aoc::day_17::find_register_value(0, goals, 0));

    return 0;
}
