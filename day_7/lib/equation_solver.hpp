#pragma once

#include "equation.hpp"
#include "operators.hpp"

namespace aoc::day_7 {

[[nodiscard]] size_t applyOperator(size_t currentResult, operator_type op, size_t value) {
    switch (op) {
    case operator_type::add:
        return currentResult + value;
    case operator_type::multiply:
        return currentResult * value;
    case operator_type::concatinate:
        {
            size_t multiplier = 10;
            size_t temp = value;
            while (temp >= 10) {
                multiplier *= 10;
                temp /= 10;
            }
            return currentResult * multiplier + value;
        }
    default:
        return currentResult;
    }
}

// Helper to try operator combinations recursively and evaluate immediately
bool tryOperatorCombinations(equation const & eq, size_t depth, size_t maxDepth, std::vector<operator_type> & current,
                             size_t currentResult) {
    if (depth == maxDepth) {
        return currentResult == eq.result;
    }

    for (size_t i = 0; i < static_cast<size_t>(operator_type::AMOUNT); ++i) {
        auto op = static_cast<operator_type>(i);
        current.push_back(op);
        size_t newResult = applyOperator(currentResult, op, eq.values[depth + 1]);

        if (tryOperatorCombinations(eq, depth + 1, maxDepth, current, newResult)) {
            return true;
        }
        current.pop_back();
    }
    return false;
}

[[nodiscard]] auto solveEquation(equation const & eq) -> std::expected<std::vector<operator_type>, std::error_code> {
    if (eq.values.empty()) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    size_t required_operators = eq.values.size() - 1;
    std::vector<operator_type> solution;

    if (tryOperatorCombinations(eq, 0, required_operators, solution, eq.values[0])) {
        return solution;
    }

    return std::unexpected(std::make_error_code(std::errc::result_out_of_range));
}

} // namespace aoc::day_7