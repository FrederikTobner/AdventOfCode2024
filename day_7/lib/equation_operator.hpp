#pragma once

#include <array>
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
template <typename T = size_t> struct equation_operator_t {
    operation_type type;                                                 ///< Type of the operation
    std::string_view name;                                               ///< String representation of the operator
    equation_result<T> (*apply)(equation_result<T>, equation_result<T>); ///< Function implementing the operation
};

/// Available operators for type T
/// @tparam T The numeric type used for calculations
template <typename T = size_t>
inline constexpr equation_operator_t<T> equationOperators_t[] = {
    {operation_type::add, " + ", [](equation_result<T> a, equation_result<T> b) { return a + b; }},
    {operation_type::multiply, " * ", [](equation_result<T> a, equation_result<T> b) { return a * b; }},
    {operation_type::concat, " || ", [](equation_result<T> a, equation_result<T> b) { return a | b; }}};

/// Size constant for basic operators (add, multiply)
/// @tparam T The numeric type used for calculations
template <typename T = size_t> inline constexpr size_t BASIC_OPERATORS_SIZE = 2;

/// Size constant for all operators (add, multiply, concat)
/// @tparam T The numeric type used for calculations
template <typename T = size_t> inline constexpr size_t ALL_OPERATORS_SIZE = 3;

/// Array type for storing operator pointers
/// @tparam T The numeric type used for calculations
template <typename T = size_t> using operator_array_t = std::array<equation_operator_t<T> const *, 3>;

template <typename T = size_t>
inline constexpr operator_array_t<T> ALL_OPERATORS_T{&equationOperators_t<T>[0], &equationOperators_t<T>[1],
                                                     &equationOperators_t<T>[2]};

template <typename T = size_t>
inline constexpr auto BASIC_OPERATORS_T = std::array{ALL_OPERATORS_T<T>[0], ALL_OPERATORS_T<T>[1]};

} // namespace aoc::day_7