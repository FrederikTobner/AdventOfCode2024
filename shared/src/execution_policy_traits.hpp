#pragma once

#include <execution>

namespace aoc::execution_policy_traits {

template <typename T> struct is_parallel_policy : std::false_type {};

template <> struct is_parallel_policy<std::execution::parallel_policy> : std::true_type {};

template <> struct is_parallel_policy<std::execution::parallel_unsequenced_policy> : std::true_type {};

template <typename T> inline constexpr bool is_parallel_policy_v = is_parallel_policy<std::remove_cvref_t<T>>::value;

} // namespace aoc::execution_policy_traits
