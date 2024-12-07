#pragma once
#include "equation.hpp"
#include "operators.hpp"
#include <span>

namespace aoc::day_7 {

inline constexpr std::array ALL_OPERATORS = {operator_type::add, operator_type::multiply, operator_type::concatinate};
inline constexpr std::array BASIC_OPERATORS = {operator_type::add, operator_type::multiply};

// Remove applyOperator implementation as it's now in operators.hpp

bool tryOperatorCombinations(equation const & eq, size_t depth, size_t maxDepth, std::vector<operator_type> & current,
                             size_t currentResult, std::span<operator_type const> allowedOperators) {
    if (depth == maxDepth) {
        return currentResult == eq.result;
    }

    for (auto op : allowedOperators) {
        current.push_back(op);
        size_t newResult = applyOperator(currentResult, op, eq.values[depth + 1]);

        if (tryOperatorCombinations(eq, depth + 1, maxDepth, current, newResult, allowedOperators)) {
            return true;
        }
        current.pop_back();
    }
    return false;
}

[[nodiscard]] auto solveEquation(equation const & eq, std::span<operator_type const> allowedOperators = ALL_OPERATORS)
    -> std::expected<std::vector<operator_type>, std::error_code> {
    if (eq.values.empty()) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    size_t required_operators = eq.values.size() - 1;
    std::vector<operator_type> solution;

    if (tryOperatorCombinations(eq, 0, required_operators, solution, eq.values[0], allowedOperators)) {
        return solution;
    }

    return std::unexpected(std::make_error_code(std::errc::result_out_of_range));
}

} // namespace aoc::day_7