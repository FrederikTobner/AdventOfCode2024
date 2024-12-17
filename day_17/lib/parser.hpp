#pragma once

#include <expected>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <system_error>
#include <vector>

#include "program.hpp"

#include "../../shared/src/parsing_rules.hpp"
#include "../../shared/src/ranges_compatibility_layer.hpp"

namespace aoc::day_17 {

// Format
// Program: 0,1,5,4,3,0
std::expected<std::vector<opcode>, std::error_code> parseOpcode(std::string_view input) {
    // Seek : to find the opcode
    auto opcode = input.substr(0, input.find(':'));
    // Split the numbers by ,
    auto numbers = input.substr(input.find(':') + 1);

    return numbers | std::views::split(',') | std::views::transform([](auto const & number) {
               auto result = aoc::parser::rules::parse_number<int64_t>(std::string_view{number});
               if (!result) {
                   throw std::invalid_argument("Failed to parse number");
               }
               return static_cast<aoc::day_17::opcode>(*result);
           }) |
           aoc::ranges::to<std::vector<aoc::day_17::opcode>>;
}

// Format
// Register A: 729
// Register B: 0
// Register C: 0
std::expected<std::array<int64_t, 3>, std::error_code> parseRegisters(std::string_view input) {
    std::array<int64_t, 3> registers;

    auto lines = input | std::views::split('\n') | std::views::transform([](auto && line) {
                     auto line_str = std::string_view{line};
                     if (line_str.back() == '\r') {
                         line_str = line_str.substr(0, line_str.size() - 1);
                     }
                     return line_str;
                 }) |
                 aoc::ranges::to<std::vector<std::string_view>>;

    if (lines.size() != 3) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    auto parsed_RegisterA = aoc::parser::rules::parse_number<int64_t>(lines[0].substr(lines[0].find(':') + 1));
    if (!parsed_RegisterA) {
        return std::unexpected(parsed_RegisterA.error());
    }
    auto parsed_RegisterB = aoc::parser::rules::parse_number<int64_t>(lines[1].substr(lines[1].find(':') + 1));
    if (!parsed_RegisterB) {
        return std::unexpected(parsed_RegisterB.error());
    }

    auto parsed_RegisterC = aoc::parser::rules::parse_number<int64_t>(lines[2].substr(lines[2].find(':') + 1));
    if (!parsed_RegisterC) {
        return std::unexpected(parsed_RegisterC.error());
    }

    registers[0] = parsed_RegisterA.value();
    registers[1] = parsed_RegisterB.value();
    registers[2] = parsed_RegisterC.value();

    return registers;
}

std::expected<program, std::error_code> parse_program(std::string_view input) {
    constexpr auto delimiters = std::array{"\r\n\r\n", "\n\n"};
    auto split_pos =
        std::ranges::find_if(delimiters, [&](auto delim) { return input.find(delim) != std::string_view::npos; });

    if (split_pos == delimiters.end()) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    auto const split_at = input.find(*split_pos);
    auto registerInit = input.substr(0, split_at);
    auto bytecode = input.substr(split_at);

    auto registers = parseRegisters(registerInit);
    if (!registers) {
        return std::unexpected(registers.error());
    }

    auto opcodes = parseOpcode(bytecode);
    if (!opcodes) {
        return std::unexpected(opcodes.error());
    }

    return program{.m_chunk = opcodes.value(),
                   .register_a = registers.value()[0],
                   .register_b = registers.value()[1],
                   .register_c = registers.value()[2]};
}

} // namespace aoc::day_17