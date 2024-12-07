#pragma once

#include <concepts>
#include <expected>
#include <span>
#include <system_error>
#include <vector>

#include "equation_operator.hpp"
#include "equation_puzzle.hpp"

namespace aoc::day_7 {

/// Checks if a puzzle is solvable using the given operators
/// @tparam T The numeric type used in the equation (defaults to size_t)
/// @param eq The puzzle to check
/// @param allowedOperators Set of operators that can be used (defaults to all operators)
/// @return true if the puzzle can be solved with the given operators
/// @throws std::system_error if the puzzle is invalid
template <typename T>
    requires std::integral<T>
[[nodiscard]] auto isSolvable(equation_puzzle<T> const & eq,
                              std::span<equation_operator_t<T> const * const> allowedOperators = ALL_OPERATORS_T<T>)
    -> bool;

/// Attempts to solve an equation puzzle using the given operators
/// @tparam T The numeric type used in the equation (defaults to size_t)
/// @param equation The puzzle to solve
/// @param allowedOperators Set of operators that can be used (defaults to all operators)
/// @return A sequence of operators that solves the puzzle, or an error if no solution exists
template <typename T>
    requires std::integral<T>
[[nodiscard]] auto
solveEquationPuzzle(equation_puzzle<T> const & equation,
                    std::span<equation_operator_t<T> const * const> allowedOperators = ALL_OPERATORS_T<T>)
    -> std::expected<std::vector<equation_operator_t<T> const *>, std::error_code>;

/// Recursively tries different operator combinations to solve the equation
/// @tparam T The numeric type used in the equation (defaults to size_t)
/// @param equation The puzzle to solve
/// @param depth Current recursion depth
/// @param maxDepth Maximum recursion depth
/// @param current Current sequence of operators being built
/// @param currentResult Intermediate result at current depth
/// @param allowedOperators Set of operators that can be used
/// @return true if a valid solution was found
template <typename T>
    requires std::integral<T>
[[nodiscard]] auto tryOperatorCombinations(equation_puzzle<T> const & equation, size_t depth, size_t maxDepth,
                                           std::vector<equation_operator_t<T> const *> & current,
                                           equation_result<T> currentResult,
                                           std::span<equation_operator_t<T> const * const> allowedOperators) -> bool;

template <typename T>
    requires std::integral<T>
[[nodiscard]] auto isSolvable(equation_puzzle<T> const & eq,
                              std::span<equation_operator_t<T> const * const> allowedOperators) -> bool {
    auto result = solveEquationPuzzle<T>(eq, allowedOperators);
    if (result) {
        return true;
    }
    if (result.error() == std::errc::result_out_of_range) {
        return false;
    }
    throw std::system_error(result.error());
}

template <typename T>
    requires std::integral<T>
[[nodiscard]] auto solveEquationPuzzle(equation_puzzle<T> const & equation,
                                       std::span<equation_operator_t<T> const * const> allowedOperators)
    -> std::expected<std::vector<equation_operator_t<T> const *>, std::error_code> {
    if (equation.values.empty()) {
        return std::unexpected(std::make_error_code(std::errc::invalid_argument));
    }

    size_t required_operators = equation.values.size() - 1;
    std::vector<equation_operator_t<T> const *> solution;

    if (tryOperatorCombinations<T>(equation, 0, required_operators, solution, equation_result<T>{equation.values[0]},
                                   allowedOperators)) {
        return solution;
    }

    return std::unexpected(std::make_error_code(std::errc::result_out_of_range));
}

template <typename T>
    requires std::integral<T>
[[nodiscard]] auto tryOperatorCombinations(equation_puzzle<T> const & equation, size_t depth, size_t maxDepth,
                                           std::vector<equation_operator_t<T> const *> & current,
                                           equation_result<T> currentResult,
                                           std::span<equation_operator_t<T> const * const> allowedOperators) -> bool {
    if (currentResult > equation.result) {
        return false;
    }
    if (depth == maxDepth) {
        return currentResult == equation.result;
    }

    for (auto const * op : allowedOperators) {
        current.push_back(op);
        equation_result<T> newResult = op->apply(currentResult, equation_result<T>{equation.values[depth + 1]});
        if (tryOperatorCombinations(equation, depth + 1, maxDepth, current, newResult, allowedOperators)) {
            return true;
        }
        current.pop_back();
    }
    return false;
}

} // namespace aoc::day_7