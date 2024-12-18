#pragma once

#include <string>

namespace aoc::day_17 {

/// @brief Operation codes for the virtual machine instructions
enum class opcode {
    ADV = 0, ///< Advance register A by division
    BXL = 1, ///< XOR operation on register B with literal
    BST = 2, ///< Store value in register B
    JNZ = 3, ///< Jump if not zero
    BXC = 4, ///< XOR operation between registers B and C
    OUT = 5, ///< Output operation
    BDV = 6, ///< Divide A and store in B
    CDV = 7, ///< Divide A and store in C
};

/// @brief Convert opcode to string representation
/// @param op The opcode to convert
/// @return String representation of the opcode
auto to_string(opcode const & op) -> std::string;

} // namespace aoc::day_17