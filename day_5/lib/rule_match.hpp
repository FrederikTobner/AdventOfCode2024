#pragma once

#include <cstdint>
#include <vector>

namespace aoc::day_5 {

struct rule_match {
    std::vector<uint8_t>::iterator pre_it;
    std::vector<uint8_t>::iterator post_it;
    auto needs_swap() const -> bool;
};
} // namespace aoc::day_5