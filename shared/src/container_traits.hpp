/**
 * @file container_traits.hpp
 * @brief Traits for container operations
 * @details Provides a generic interface for container operations like insertion and reservation,
 * allowing algorithms to work with different container types uniformly.
 */

#pragma once

#include <array>
#include <set>
#include <type_traits>
#include <vector>

namespace aoc::container {

/// @brief Primary template for container operations
/// @tparam CONTAINER The container type to provide operations for
template <typename CONTAINER> struct container_traits {
    /// @brief Inserts a value into the container
    /// @tparam T The type of value to insert
    /// @param container The container to insert into
    /// @param value The value to insert
    template <typename T> static void insert(CONTAINER & container, T && value) {
        if constexpr (requires { container.push_back(std::forward<T>(value)); }) {
            container.push_back(std::forward<T>(value));
        } else if constexpr (requires { container.insert(std::forward<T>(value)); }) {
            container.insert(std::forward<T>(value));
        } else {
            static_assert(always_false<T>, "Container must support either push_back or insert");
        }
    }

    /// @brief Reserves space in the container if supported
    /// @param container The container to reserve space in
    /// @param size The amount of space to reserve
    static void reserve(CONTAINER & container, size_t size) {
        if constexpr (requires { container.reserve(size); }) {
            container.reserve(size);
        }
    }

  private:
    template <typename T> static constexpr bool always_false = false;
};

/// @brief Specialization for fixed-size arrays
template <typename T, size_t SIZE> struct container_traits<std::array<T, SIZE>> {
    static_assert(SIZE > 0, "Array size must be greater than 0");

    /// @brief Inserts a value into the array at the next available position
    /// @tparam CONVERTABLE The type of value to insert (must be convertible to T)
    /// @param container The array to insert into
    /// @param value The value to insert
    template <typename CONVERTABLE> static void insert(std::array<T, SIZE> & container, CONVERTABLE && value) {
        static size_t index = 0;
        if (index < SIZE) {
            container[index++] = std::forward<CONVERTABLE>(value);
        }
    }

    /// @brief No-op for arrays (fixed size)
    static void reserve(std::array<T, SIZE> &, size_t) {
    }
};

} // namespace aoc::container