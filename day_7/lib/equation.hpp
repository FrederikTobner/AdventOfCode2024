#pragma once

#include <cstdint>
#include <format>
#include <string>
#include <vector>

namespace aoc::day_7 {

struct equation {
    size_t result;
    std::vector<uint16_t> values;
    std::string toString() const {
        return std::format("{}", result);
    }
};

} // namespace aoc::day_7
