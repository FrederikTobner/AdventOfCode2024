/**
 * @file execution_policy_traits.hpp
 * @brief Traits to determine execution policy characteristics
 * @details Provides type traits to identify parallel execution policies,
 * helping functions determine optimal processing strategies.
 */

#pragma once

#include <execution>

namespace aoc::execution_policy_traits {

/// @brief Type trait to identify parallel execution policies
template <typename T> struct is_parallel_policy : std::false_type {};

/// @brief Specialization for std::execution::parallel_policy
template <> struct is_parallel_policy<std::execution::parallel_policy> : std::true_type {};

/// @brief Specialization for std::execution::parallel_unsequenced_policy
template <> struct is_parallel_policy<std::execution::parallel_unsequenced_policy> : std::true_type {};

/// @brief Helper variable template to check if a type is a parallel execution policy
template <typename T> inline constexpr bool is_parallel_policy_v = is_parallel_policy<std::remove_cvref_t<T>>::value;

} // namespace aoc::execution_policy_traits
