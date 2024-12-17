#pragma once

#include <format>
#include <string>
#include <vector>

#include "opcode.hpp"

namespace aoc::day_17 {

struct chunk {
    std::vector<opcode> m_data;
    std::string to_string() const {
        size_t memory_address = 0;
        std::string result;
        for (auto const & op : m_data) {
            result += std::format("{:04x}: {}\n", memory_address, ::aoc::day_17 ::to_string(op));
            memory_address += 3;
        }
        return result;
    }

    auto operator[](size_t index) const -> opcode const & {
        return m_data[index];
    }

    auto size() const -> size_t {
        return m_data.size();
    }
};
} // namespace aoc::day_17