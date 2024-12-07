#pragma once
#include <cstddef>

namespace aoc::day_7 {

enum class operator_type {
    add,
    multiply,
    concatinate,
    AMOUNT // Only used for loops
};

namespace detail {
[[nodiscard]] inline size_t add(size_t a, size_t b) {
    return a + b;
}
[[nodiscard]] inline size_t multiply(size_t a, size_t b) {
    return a * b;
}
[[nodiscard]] inline size_t concatinate(size_t a, size_t b) {
    size_t multiplier = 10;
    size_t temp = b;
    while (temp >= 10) {
        multiplier *= 10;
        temp /= 10;
    }
    return a * multiplier + b;
}
} // namespace detail

[[nodiscard]] inline size_t applyOperator(size_t currentResult, operator_type op, size_t value) {
    switch (op) {
    case operator_type::add:
        return detail::add(currentResult, value);
    case operator_type::multiply:
        return detail::multiply(currentResult, value);
    case operator_type::concatinate:
        return detail::concatinate(currentResult, value);
    default:
        return currentResult;
    }
}

} // namespace aoc::day_7