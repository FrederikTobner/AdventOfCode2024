#pragma once

#include <string>
#include <vector>

#include "chunk.hpp"
#include "opcode.hpp"
#include "program.hpp"

namespace aoc::day_17 {

[[nodiscard]] auto transpile(program const & program_to_transpile) -> std::string;

[[nodiscard]] auto extract_helpers(chunk const & bytecode) -> std::string;
} // namespace aoc::day_17