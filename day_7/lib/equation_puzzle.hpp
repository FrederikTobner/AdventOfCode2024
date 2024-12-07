#pragma once
#include "equation_result.hpp"
#include <cstdint>
#include <format>
#include <string>
#include <vector>

namespace aoc::day_7 {

struct equation_puzzle {
    equation_result<> result;
    std::vector<uint16_t> values;
    std::string toString() const {
        return std::format("{}", result.raw());
    }
};

} // namespace aoc::day_7
