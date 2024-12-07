#pragma once
#include "equation_result.hpp"

#include <cstdint>
#include <vector>

namespace aoc::day_7 {

/// Represents a puzzle consisting of a target result and a sequence of values
/// that need to be combined using operators to reach that result
/// @tparam T The numeric type used for the result value (defaults to size_t)
template <typename T = size_t> struct equation_puzzle {
    equation_result<T> result;    ///< The target result that needs to be achieved
    std::vector<uint16_t> values; ///< The sequence of values that need to be combined
};

} // namespace aoc::day_7
