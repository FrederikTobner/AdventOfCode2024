#pragma once

#include <cmath>
#include <concepts>

namespace aoc::math {
template <typename T = float>
    requires std::is_arithmetic_v<T>
class vector_2d {
  public:
    T x;
    T y;

    constexpr vector_2d() : x(0), y(0) {
    }
    constexpr vector_2d(T x, T y) : x(x), y(y) {
    }

    auto operator+(vector_2d const & other) const -> vector_2d {
        return vector_2d(x + other.x, y + other.y);
    }

    auto operator-(vector_2d const & other) const -> vector_2d {
        return vector_2d(x - other.x, y - other.y);
    }

    auto operator*(T scalar) const -> vector_2d {
        return vector_2d(x * scalar, y * scalar);
    }

    auto operator/(T scalar) const -> vector_2d {
        return vector_2d(x / scalar, y / scalar);
    }

    auto operator==(vector_2d const & other) const -> bool {
        return x == other.x && y == other.y;
    }

    auto operator!=(vector_2d const & other) const -> bool {
        return !(*this == other);
    }

    auto operator+=(vector_2d const & other) -> vector_2d & {
        x += other.x;
        y += other.y;
        return *this;
    }

    auto operator-=(vector_2d const & other) -> vector_2d & {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    auto operator*=(T scalar) -> vector_2d & {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    auto operator/=(T scalar) -> vector_2d & {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    auto dot(vector_2d const & other) const -> T {
        return x * other.x + y * other.y;
    }

    auto cross(vector_2d const & other) const -> T {
        return x * other.y - y * other.x;
    }

    auto magnitude() const -> T {
        return std::sqrt(x * x + y * y);
    }

    auto normalize() -> vector_2d {
        return *this / magnitude();
    }
};

} // namespace aoc::math

namespace std {
template <typename T> struct hash<aoc::math::vector_2d<T>> {
    auto operator()(aoc::math::vector_2d<T> const & v) const -> size_t {
        return hash<T>{}(v.x) ^ hash<T>{}(v.y);
    }
};
} // namespace std