#pragma once

#include <array>
#include <set>
#include <type_traits>
#include <vector>

namespace aoc::container {

// Primary template
template <typename Container> struct container_traits {
    template <typename T> static void insert(Container & container, T && value) {
        if constexpr (requires { container.push_back(std::forward<T>(value)); }) {
            container.push_back(std::forward<T>(value));
        } else if constexpr (requires { container.insert(std::forward<T>(value)); }) {
            container.insert(std::forward<T>(value));
        } else {
            static_assert(always_false<T>, "Container must support either push_back or insert");
        }
    }

    static void reserve(Container & container, size_t size) {
        if constexpr (requires { container.reserve(size); }) {
            container.reserve(size);
        }
    }

  private:
    template <typename T> static constexpr bool always_false = false;
};

template <typename T, size_t N> struct container_traits<std::array<T, N>> {
    static_assert(N > 0, "Array size must be greater than 0");

    template <typename U> static void insert(std::array<T, N> & container, U && value) {
        static size_t index = 0;
        if (index < N) {
            container[index++] = std::forward<U>(value);
        }
    }

    static void reserve(std::array<T, N> &, size_t) {
        // Arrays have fixed size, no reserve needed
    }
};

} // namespace aoc::container