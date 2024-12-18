#include "chunk.hpp"

namespace aoc::day_17 {

auto to_combo_operand_literal(int64_t & operand) -> std::string {
    switch (operand) {
    case 4:
        return "a";
    case 5:
        return "b";
    case 6:
        return "c";
    case 7:
        throw std::runtime_error("Invalid operand");
    default:
        return std::to_string(operand);
    }
}

auto chunk::to_string() const -> std::string {
    size_t memory_address = 0;
    std::string result;
    for (size_t i = 0; i < m_data.size(); i += 2) {
        auto opcode = m_data[i];
        switch (opcode) {
        case opcode::ADV:
        case opcode::BST:
        case opcode::BDV:
        case opcode::CDV:
            {
                auto operand = static_cast<int64_t>(m_data[i + 1]);
                result += std::format("{:03}: {} {}\n", memory_address, ::aoc::day_17::to_string(opcode),
                                      to_combo_operand_literal(operand));
                break;
            }
        }
    }
    return result;
}

auto chunk::operator[](size_t index) const -> opcode const & {
    return m_data[index];
}

auto chunk::size() const -> size_t {
    return m_data.size();
}

} // namespace aoc::day_17