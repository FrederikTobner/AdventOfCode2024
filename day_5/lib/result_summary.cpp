#include "result_summary.hpp"

auto aoc::day_5::result_summary::add(uint64_t value, bool isValid) -> void {
    if (isValid) {
        valid_ += value;
    } else {
        invalid_ += value;
    }
}