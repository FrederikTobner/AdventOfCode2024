#pragma once
#include <array>
#include <cstddef>
#include <string_view>

#include "equation_result.hpp"

namespace aoc::day_7 {

enum class op_type {
    add,
    multiply,
    concat
};

struct operator_desc {
    op_type type;
    std::string_view name;
    equation_result<> (*operation)(equation_result<>, equation_result<>);
};

inline constexpr operator_desc operators[] = {
    {op_type::add, " + ", [](equation_result<> a, equation_result<> b) { return a + b; }},
    {op_type::multiply, " * ", [](equation_result<> a, equation_result<> b) { return a * b; }},
    {op_type::concat, " || ", [](equation_result<> a, equation_result<> b) { return a | b; }}};

inline operator_desc const * BASIC_OPERATORS[] = {&operators[0], &operators[1]};
inline operator_desc const * ALL_OPERATORS[] = {&operators[0], &operators[1], &operators[2]};

} // namespace aoc::day_7