#pragma once

#include <format>
#include <string>
#include <vector>

#include "opcode.hpp"

namespace aoc::day_17 {

[[nodiscard]] auto to_combo_operand_literal(int64_t & operand) -> std::string;

struct chunk {
    std::vector<opcode> m_data;
    auto to_string() const -> std::string;

    [[nodiscard]] auto operator[](size_t index) const -> opcode const &;

    [[nodiscard]] auto size() const -> size_t;
};
} // namespace aoc::day_17