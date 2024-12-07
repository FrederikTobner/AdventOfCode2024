#pragma once
#include "equation_result.hpp"

#include <cstdint>
#include <vector>

namespace aoc::day_7 {

struct equation_puzzle {
    equation_result<> result;
    std::vector<uint16_t> values;
};

} // namespace aoc::day_7
