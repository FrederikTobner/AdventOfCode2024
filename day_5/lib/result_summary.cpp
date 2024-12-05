#include "result_summary.hpp"

void aoc::day_5::result_summary::add(uint64_t value, bool isValid) {
    if (isValid) {
        valid_ += value;
    } else {
        invalid_ += value;
    }
}