#include "transpiler.hpp"

namespace aoc::day_17 {

[[nodiscard]] auto transpile(program const & program_to_transpile) -> std::string {
    std::string result = R"(#pragma once
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

void run_using_best_lang() {
bool first_out = true;)";

    result += "    int64_t a = " + std::to_string(program_to_transpile.register_a) + ";\n";
    result += "    int64_t b = " + std::to_string(program_to_transpile.register_b) + ";\n";
    result += "    int64_t c = " + std::to_string(program_to_transpile.register_c) + ";\n";

    for (size_t i = 0; i < program_to_transpile.m_chunk.size(); i += 2) {
        result += "_" + std::to_string(i * 5) + ": ";
        auto op = program_to_transpile.m_chunk[i];
        auto operand =
            i + 1 < program_to_transpile.m_chunk.size() ? static_cast<int64_t>(program_to_transpile.m_chunk[i + 1]) : 0;
        switch (op) {
        case opcode::ADV:
            {
                if (operand < 4) {
                    result += "    a = a / " + std::to_string((uint8_t)std::pow(2, operand)) + ";\n";
                } else {
                    result += "    a = a / std::pow(2, " + to_combo_operand_literal(operand) + ");\n";
                }
                break;
            }
        case opcode::BXL:
            result += "    b ^= " + std::to_string(operand) + ";\n";
            break;
        case opcode::BST:
            result += "    b = " + to_combo_operand_literal(operand) + " % 8;\n";
            break;
        case opcode::JNZ:
            result += "    if (a != 0) goto _" + std::to_string(operand) + ";\n";
            break;
        case opcode::BXC:
            result += "    b ^= c;\n";
            break;
        case opcode::OUT:
            result += R"(if(first_out) {
                std::cout << )";
            result += to_combo_operand_literal(operand) + R"( % 8 << std::endl;
                first_out = false;
                } else {
                std::cout << "," << )";
            result += to_combo_operand_literal(operand) + R"( % 8 << std::endl;
                }
                )";
            break;
        case opcode::BDV:
            {
                if (operand < 4) {
                    result += "    b = a / " + std::to_string((uint8_t)std::pow(2, operand)) + ";\n";
                } else {
                    result += "    b = a / std::pow(2, " + to_combo_operand_literal(operand) + ");\n";
                }
                break;
            }
        case opcode::CDV:
            {
                if (operand < 4) {
                    result += "    c = a / " + std::to_string((uint8_t)std::pow(2, operand)) + ";\n";
                } else {
                    result += "    c = a / std::pow(2, " + to_combo_operand_literal(operand) + ");\n";
                }
                break;
            }
        }
    }

    result += R"( if (!first_out) {
    std::cout << std::endl;
    }   
    return;\n)";
    result += "}\n";

    return result;
}

[[nodiscard]] auto extract_helpers(chunk const & bytecode) -> std::string {
    std::string result = R"(#pragma once
#include <cmath>
#include <cstdint>
#include <vector>

auto calculate_byte(int64_t a) -> int64_t {
)";
    result += "    int64_t b = 0, c = 0;\n";

    for (size_t i = 0; i < bytecode.size(); i += 2) {
        auto op = bytecode[i];
        auto operand = i + 1 < bytecode.size() ? static_cast<int64_t>(bytecode[i + 1]) : 0;

        switch (op) {
        case opcode::ADV:
            {
                if (operand < 4) {
                    result += "a = a / " + std::to_string((uint8_t)std::pow(2, operand)) + ";\n";
                } else {
                    result += "a = a / std::pow(2, " + to_combo_operand_literal(operand) + ");\n";
                }
                break;
            }
        case opcode::BXL:
            result += "b ^= " + std::to_string(operand) + ";\n";
            break;
        case opcode::BST:
            result += "b = " + to_combo_operand_literal(operand) + " % 8;\n";
            break;
        case opcode::BXC:
            result += "b ^= c;\n";
            break;
        case opcode::BDV:
            {
                if (operand < 4) {
                    result += "b = a / " + std::to_string((uint8_t)std::pow(2, operand)) + ";\n";
                } else {
                    result += "b = a / std::pow(2, " + to_combo_operand_literal(operand) + ");\n";
                }
                break;
            }
        case opcode::CDV:
            {
                if (operand < 4) {
                    result += "c = a / " + std::to_string((uint8_t)std::pow(2, operand)) + ";\n";
                } else {
                    result += "c = a / std::pow(2, " + to_combo_operand_literal(operand) + ");\n";
                }
                break;
            }
        default:
            break;
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