#pragma once
#include "equation_puzzle.hpp"
#include "operators.hpp"
#include <span>

namespace aoc::day_7 {

// Update span type to be more specific
using operator_span = std::span<operator_desc const * const>;

bool tryOperatorCombinations(equation_puzzle const & equation, size_t depth, size_t maxDepth,
                             std::vector<operator_desc const *> & current, equation_result<> currentResult,
                             operator_span allowedOperators) {
    if (depth == maxDepth) {
        return currentResult == equation.result;
    }

    for (auto const * op : allowedOperators) {
        current.push_back(op);
        equation_result<> newResult = op->operation(currentResult, equation_result<>{equation.values[depth + 1]});

        if (tryOperatorCombinations(equation, depth + 1, maxDepth, current, newResult, allowedOperators)) {
            return true;
        }
        current.pop_back();
    }
    return false;
}

[[nodiscard]] auto solveEquationPuzzle(equation_puzzle const & equation, operator_span allowedOperators = ALL_OPERATORS)
    -> std::expected<std::vector<operator_desc const *>, std::error_code> {
    if (equation.values.empty()) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    size_t required_operators = equation.values.size() - 1;
    std::vector<operator_desc const *> solution;

    if (tryOperatorCombinations(equation, 0, required_operators, solution, equation_result<>{equation.values[0]},
                                allowedOperators)) {
        return solution;
    }

    return std::unexpected(std::make_error_code(std::errc::result_out_of_range));
}

[[nodiscard]] auto isSolvable(equation_puzzle const & eq, operator_span allowedOperators = ALL_OPERATORS) -> bool {
    auto result = solveEquationPuzzle(eq, allowedOperators);
    if (result) {
        return true;
    }
    if (result.error() == std::errc::result_out_of_range) {
        return false;
    }
    throw std::system_error(result.error());
}

} // namespace aoc::day_7