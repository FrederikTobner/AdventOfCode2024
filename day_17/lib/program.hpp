#pragma once

#include <expected>
#include <string>
#include <system_error>
#include <vector>

#include "chunk.hpp"
#include "opcode.hpp"

namespace aoc::day_17 {
struct program {
    chunk m_chunk;
    int64_t register_a;
    int64_t register_b;
    int64_t register_c;
};
} // namespace aoc::day_17