#pragma once

#include <cstdint>
#include <functional>
#include <vector>

#include "opcode.hpp"
#include "program.hpp"

namespace aoc::day_17 {

class virtual_machine {
  public:
    virtual_machine(std::function<void(std::string_view)> output) : m_output{output} {
    }
    ~virtual_machine() = default;

    void execute(program const & prog);

  private:
    size_t m_instruction_pointer;
    int64_t m_register_a;
    int64_t m_register_b;
    int64_t m_register_c;
    std::function<void(std::string_view)> m_output;

    int64_t convertToComboOperand(int64_t & operand);
};

} // namespace aoc::day_17