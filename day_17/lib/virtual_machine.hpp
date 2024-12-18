#pragma once

#include <cstdint>
#include <functional>
#include <vector>

#include "opcode.hpp"
#include "program.hpp"

namespace aoc::day_17 {

class virtual_machine {
  public:
    virtual_machine(std::function<void(std::string_view)> output);
    ~virtual_machine() = default;

    auto execute(program const & prog) -> void;

  private:
    size_t m_instruction_pointer;
    int64_t m_register_a;
    int64_t m_register_b;
    int64_t m_register_c;
    std::function<void(std::string_view)> m_output;

    [[nodiscard]] auto to_combo_operand(int64_t & operand) -> int64_t;
};

} // namespace aoc::day_17