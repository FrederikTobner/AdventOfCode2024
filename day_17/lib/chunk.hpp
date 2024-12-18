#pragma once

#include <format>
#include <string>
#include <vector>

#include "opcode.hpp"

namespace aoc::day_17 {

/// @brief Converts an operand to a literal string representation
/// @param operand The operand to convert
/// @return String representation of the operand
[[nodiscard]] auto to_combo_operand_literal(int64_t & operand) -> std::string;

/// @brief Represents a sequence of opcodes forming a program chunk
struct chunk {
    std::vector<opcode> m_data; ///< The sequence of opcodes

    /// @brief Converts the chunk to a string representation
    /// @return String representation of the chunk
    auto to_string() const -> std::string;

    /// @brief Access operator for opcodes in the chunk
    /// @param index The index of the opcode to access
    /// @return Reference to the opcode at the given index
    [[nodiscard]] auto operator[](size_t index) const -> opcode const &;

    /// @brief Gets the size of the chunk
    /// @return Number of opcodes in the chunk
    [[nodiscard]] auto size() const -> size_t;
};

} // namespace aoc::day_17