#include "transpiler.hpp"

#include <cmath>
#include <cstdint>
#include <format>
#include <iostream>
#include <string_view>

namespace aoc::day_17 {

namespace {
constexpr std::string_view PROGRAM_HEADER = R"(#pragma once
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

void run_using_best_lang() {
bool first_out = true;)";

constexpr std::string_view HELPERS_HEADER = R"(#pragma once
#include <cmath>
#include <cstdint>
#include <vector>

auto calculate_byte(int64_t a) -> int64_t {
)";

namespace opcode_translation {
static auto translate_div_operation(std::string const & target, int64_t operand) -> std::string {
    if (operand < 4) {
        return std::format("    {} = {} / {};\n", target, target, static_cast<uint8_t>(std::pow(2, operand)));
    }
    return std::format("    {} = {} / std::pow(2, {});\n", target, target, to_combo_operand_literal(operand));
}

static auto translate_output(int64_t operand) -> std::string {
    return std::format(R"(    if(first_out) {{
        std::cout << {} % 8 << std::endl;
        first_out = false;
    }} else {{
        std::cout << "," << {} % 8 << std::endl;
    }}
)",
                       to_combo_operand_literal(operand), to_combo_operand_literal(operand));
}

auto translate_opcode(opcode op, int64_t operand, size_t label_index = 0) -> std::string {
    switch (op) {
    case opcode::ADV:
        return translate_div_operation("a", operand);
    case opcode::BXL:
        return std::format("    b ^= {};\n", operand);
    case opcode::BST:
        return std::format("    b = {} % 8;\n", to_combo_operand_literal(operand));
    case opcode::JNZ:
        return std::format("    if (a != 0) goto _{};\n", operand);
    case opcode::BXC:
        return "    b ^= c;\n";
    case opcode::OUT:
        return translate_output(operand);
    case opcode::BDV:
        return translate_div_operation("b", operand);
    case opcode::CDV:
        return translate_div_operation("c", operand);
    default:
        return "";
    }
}
} // namespace opcode_translation

auto initialize_registers(program const & prog) -> std::string {
    return std::format("    int64_t a = {};\n    int64_t b = {};\n    int64_t c = {};\n", prog.register_a,
                       prog.register_b, prog.register_c);
}

} // anonymous namespace

auto transpile(program const & program_to_transpile) -> std::string {
    std::string result{PROGRAM_HEADER};
    result += initialize_registers(program_to_transpile);

    for (size_t i = 0; i < program_to_transpile.m_chunk.size(); i += 2) {
        auto const [op, operand] =
            std::tuple{program_to_transpile.m_chunk[i], i + 1 < program_to_transpile.m_chunk.size()
                                                            ? static_cast<int64_t>(program_to_transpile.m_chunk[i + 1])
                                                            : 0};

        result += "_" + std::to_string(i * 5) + ": ";
        result += opcode_translation::translate_opcode(op, operand);
    }

    result += R"( if (!first_out) {
    std::cout << std::endl;
    }   
    return;
}
)";
    return result;
}

auto extract_helpers(chunk const & bytecode) -> std::string {
    std::string result{HELPERS_HEADER};
    result += "    int64_t b = 0, c = 0;\n";

    for (size_t i = 0; i < bytecode.size(); i += 2) {
        auto const [op, operand] =
            std::tuple{bytecode[i], i + 1 < bytecode.size() ? static_cast<int64_t>(bytecode[i + 1]) : 0};

        if (op != opcode::JNZ && op != opcode::OUT) {
            result += opcode_translation::translate_opcode(op, operand);
        }
    }

    result += "}\n";
    result +=
        R"(int64_t find_register_value(int64_t desired_register_value, std::vector<int64_t> const & goals, int currentIndex) {
    for (int i = 0; i < 8; i++) {
        if (calculate_byte(desired_register_value + i) == goals[currentIndex]) {
            if (currentIndex + 1 == goals.size()) {
                return desired_register_value + 3;
            }
            int64_t result = find_register_value((desired_register_value + i) << 3, goals, currentIndex + 1);
            if (result != -1) {
                return result;
            }
        }
    }
    return -1;
})";
    return result;
}

} // namespace aoc::day_17