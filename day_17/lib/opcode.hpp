#pragma once

#include <string>

namespace aoc::day_17 {

enum class opcode {
    ADV = 0,
    BXL = 1,
    BST = 2,
    JNZ = 3,
    BXC = 4,
    OUT = 5,
    BDV = 6,
    CDV = 7,
};

std::string to_string(opcode const & op);
} // namespace aoc::day_17