#pragma once

#include <string>
#include <vector>

#include "chunk.hpp"
#include "opcode.hpp"
#include "program.hpp"

namespace aoc::day_17 {

/// @brief Transpiles a virtual machine program into C++ code
/// @param program_to_transpile The program to transpile
/// @return String containing the generated C++ code
[[nodiscard]] auto transpile(program const & program_to_transpile) -> std::string;

/// @brief Extracts helper functions needed for program execution
/// @param bytecode The bytecode to analyze for helper function generation
/// @return String containing the generated helper function definitions
[[nodiscard]] auto extract_helpers(chunk const & bytecode) -> std::string;

} // namespace aoc::day_17