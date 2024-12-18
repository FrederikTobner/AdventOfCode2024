#include "parser.hpp"

namespace aoc::day_17 {

[[nodiscard]] static auto parse_opcode(std::string_view input) -> std::expected<std::vector<opcode>, std::error_code>;

[[nodiscard]] static auto parse_registers(std::string_view input)
    -> std::expected<std::array<int64_t, 3>, std::error_code>;

[[nodiscard]] auto parse_program(std::string_view input) -> std::expected<program, std::error_code> {
    constexpr auto delimiters = std::array{"\r\n\r\n", "\n\n"};
    auto split_pos =
        std::ranges::find_if(delimiters, [&](auto delim) { return input.find(delim) != std::string_view::npos; });

    if (split_pos == delimiters.end()) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    auto const split_at = input.find(*split_pos);
    auto registerInit = input.substr(0, split_at);
    auto bytecode = input.substr(split_at);

    auto registers = parse_registers(registerInit);
    if (!registers) {
        return std::unexpected(registers.error());
    }

    auto opcodes = parse_opcode(bytecode);
    if (!opcodes) {
        return std::unexpected(opcodes.error());
    }

    return program{.m_chunk = opcodes.value(),
                   .register_a = registers.value()[0],
                   .register_b = registers.value()[1],
                   .register_c = registers.value()[2]};
}

[[nodiscard]] static auto parse_opcode(std::string_view input) -> std::expected<std::vector<opcode>, std::error_code> {
    auto opcode = input.substr(0, input.find(':'));
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

[[nodiscard]] static auto parse_registers(std::string_view input)
    -> std::expected<std::array<int64_t, 3>, std::error_code> {
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

} // namespace aoc::day_17