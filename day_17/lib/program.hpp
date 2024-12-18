#pragma once

#include <expected>
#include <string>
#include <system_error>
#include <vector>

#include "chunk.hpp"
#include "opcode.hpp"

namespace aoc::day_17 {

/// @brief Represents a complete program for the virtual machine
/// @details Contains the program bytecode and initial register values
struct program {
    chunk m_chunk;      ///< The program's bytecode
    int64_t register_a; ///< Initial value for register A
    int64_t register_b; ///< Initial value for register B
    int64_t register_c; ///< Initial value for register C
};

} // namespace aoc::day_17