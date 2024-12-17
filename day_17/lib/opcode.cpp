#include "opcode.hpp"

namespace aoc::day_17 {

std::string to_string(opcode const & op) {
    switch (op) {
    case opcode::ADV:
        return "ADV";
    case opcode::BXL:
        return "BXL";
    case opcode::BST:
        return "BST";
    case opcode::JNZ:
        return "JNZ";
    case opcode::BXC:
        return "BXC";
    case opcode::OUT:
        return "OUT";
    case opcode::BDV:
        return "BDV";
    case opcode::CDV:
        return "CDV";
    }
    return "UNKNOWN";
}

} // namespace aoc::day_17