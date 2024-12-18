#pragma once

#include <cstdint>
#include <functional>
#include <vector>

#include "opcode.hpp"
#include "program.hpp"

class VirtualMachineTest;

namespace aoc::day_17 {

/// @brief Virtual machine for executing bytecode programs
/// @details Implements a register-based virtual machine with three registers
/// and support for basic arithmetic and control flow operations
class virtual_machine {
    friend class ::VirtualMachineTest;

  public:
    /// @brief Constructs a virtual machine with output callback
    /// @param output Function to handle output operations
    virtual_machine(std::function<void(std::string_view)> output);
    ~virtual_machine() = default;

    /// @brief Executes a program on the virtual machine
    /// @param prog The program to execute
    auto execute(program const & prog) -> void;

  private:
    size_t m_instruction_pointer;                   ///< Current instruction pointer
    int64_t m_register_a;                           ///< Register A value
    int64_t m_register_b;                           ///< Register B value
    int64_t m_register_c;                           ///< Register C value
    std::function<void(std::string_view)> m_output; ///< Output callback function

    /// @brief Converts an operand to its combined value
    /// @param operand The operand to convert
    /// @return The combined operand value
    [[nodiscard]] auto to_combo_operand(int64_t & operand) -> int64_t;
};

} // namespace aoc::day_17