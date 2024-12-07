#pragma once

#include <array>
#include <concepts>
#include <string_view>

#include "equation_result.hpp"

namespace aoc::day_7 {

/// Represents the different types of operations available
enum class operation_type {
    add,      ///< Addition operation
    multiply, ///< Multiplication operation
    concat    ///< Digit concatenation operation
};

/// Represents an operator that can be applied to equation results
/// @tparam T The numeric type used for calculations (defaults to size_t)
template <typename T = size_t>
    requires std::integral<T>
struct equation_operator_t {
    operation_type type;                                                 ///< Type of the operation
    std::string_view name;                                               ///< String representation of the operator
    equation_result<T> (*apply)(equation_result<T>, equation_result<T>); ///< Function implementing the operation
};                                                                       // namespace aoc::day_7

/// Available operators for type T
/// @tparam T The numeric type used for calculations
template <typename T = size_t>
    requires std::integral<T>
inline constexpr equation_operator_t<T> equationOperators_t[] = {
    {operation_type::add, " + ", [](equation_result<T> a, equation_result<T> b) { return a + b; }},
    {operation_type::multiply, " * ", [](equation_result<T> a, equation_result<T> b) { return a * b; }},
    {operation_type::concat, " || ", [](equation_result<T> a, equation_result<T> b) { return a | b; }}};

template <typename T = size_t>
    requires std::integral<T>
inline constexpr std::array<equation_operator_t<T> const *, 3> ALL_OPERATORS_T{
    &equationOperators_t<T>[0], &equationOperators_t<T>[1], &equationOperators_t<T>[2]};

template <typename T = size_t>
    requires std::integral<T>
inline constexpr auto BASIC_OPERATORS_T = std::array{ALL_OPERATORS_T<T>[0], ALL_OPERATORS_T<T>[1]};

} // namespace aoc::day_7