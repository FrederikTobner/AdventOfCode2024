#include "virtual_machine.hpp"

#include <cmath>

namespace aoc::day_17 {

int64_t virtual_machine::convertToComboOperand(int64_t & operand) {
    switch (operand) {
    case 4:
        return m_register_a;
    case 5:
        return m_register_b;
    case 6:
        return m_register_c;
    case 7:
        throw std::runtime_error("Invalid operand");
    default:
        return operand;
    }
}

void virtual_machine::execute(program const & prog) {
    m_instruction_pointer = 0;
    m_register_a = prog.register_a;
    m_register_b = prog.register_b;
    m_register_c = prog.register_c;

    while (m_instruction_pointer < prog.m_chunk.size() - 1) {
        auto const & op = prog.m_chunk[m_instruction_pointer++];
        auto operand = static_cast<int64_t>(prog.m_chunk[m_instruction_pointer++]);
        switch (op) {
        case opcode::ADV:
            m_register_a /= std::pow(2, convertToComboOperand(operand));
            break;
        case opcode::BXL:
            m_register_b ^= operand;
            break;
        case opcode::BST:
            m_register_b = convertToComboOperand(operand) % 8;
            break;
        case opcode::JNZ:
            if (m_register_a != 0) {
                m_instruction_pointer = operand;
            }
            break;
        case opcode::BXC:
            m_register_b ^= m_register_c;
            break;
        case opcode::OUT:
            m_output(std::to_string(convertToComboOperand(operand) % 8));
            break;
        case opcode::BDV:
            m_register_b = m_register_a / std::pow(2, convertToComboOperand(operand));
            break;
        case opcode::CDV:
            m_register_c = m_register_a / std::pow(2, convertToComboOperand(operand));
            break;
        }
    }
}

} // namespace aoc::day_17