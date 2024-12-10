#pragma once

#include <cmath>
#include <concepts>


namespace aoc::math {
template <typename T = float>
    requires std::is_arithmetic_v<T>
class Vector2D {
  public:
    T x;
    T y;

    Vector2D() : x(0), y(0) {
    }
    Vector2D(T x, T y) : x(x), y(y) {
    }

    auto operator+(Vector2D const & other) const -> Vector2D {
        return Vector2D(x + other.x, y + other.y);
    }

    auto operator-(Vector2D const & other) const -> Vector2D {
        return Vector2D(x - other.x, y - other.y);
    }

    auto operator*(T scalar) const -> Vector2D {
        return Vector2D(x * scalar, y * scalar);
    }

    auto operator/(T scalar) const -> Vector2D {
        return Vector2D(x / scalar, y / scalar);
    }

    auto operator==(Vector2D const & other) const -> bool {
        return x == other.x && y == other.y;
    }

    auto operator!=(Vector2D const & other) const -> bool {
        return !(*this == other);
    }

    auto operator+=(Vector2D const & other) -> Vector2D & {
        x += other.x;
        y += other.y;
        return *this;
    }

    auto operator-=(Vector2D const & other) -> Vector2D & {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    auto operator*=(T scalar) -> Vector2D & {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    auto operator/=(T scalar) -> Vector2D & {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    auto dot(Vector2D const & other) const -> T {
        return x * other.x + y * other.y;
    }

    auto cross(Vector2D const & other) const -> T {
        return x * other.y - y * other.x;
    }

    auto magnitude() const -> T {
        return std::sqrt(x * x + y * y);
    }

    auto normalize() -> Vector2D {
        return *this / magnitude();
    }
};

} // namespace aoc::math

namespace std {
template <typename T> struct hash<aoc::math::Vector2D<T>> {
    auto operator()(aoc::math::Vector2D<T> const & v) const -> size_t {
        return hash<T>{}(v.x) ^ hash<T>{}(v.y);
    }
};
} // namespace std