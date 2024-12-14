#pragma once

#include <cmath>
#include <concepts>
#include <format>
#include <string>
#include <string_view>

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

    constexpr auto operator+(vector_2d const & other) const -> vector_2d {
        return vector_2d(x + other.x, y + other.y);
    }

    constexpr auto operator-(vector_2d const & other) const -> vector_2d {
        return vector_2d(x - other.x, y - other.y);
    }

    constexpr auto operator*(T scalar) const -> vector_2d {
        return vector_2d(x * scalar, y * scalar);
    }

    constexpr auto operator/(T scalar) const -> vector_2d {
        return vector_2d(x / scalar, y / scalar);
    }

    constexpr auto operator==(vector_2d const & other) const -> bool {
        return x == other.x && y == other.y;
    }

    constexpr auto operator!=(vector_2d const & other) const -> bool {
        return !(*this == other);
    }

    constexpr auto operator+=(vector_2d const & other) -> vector_2d & {
        x += other.x;
        y += other.y;
        return *this;
    }

    constexpr auto operator-=(vector_2d const & other) -> vector_2d & {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    constexpr auto operator*=(T scalar) -> vector_2d & {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    constexpr auto operator/=(T scalar) -> vector_2d & {
        x /= scalar;
        y /= scalar;
        return *this;
    }

    constexpr auto dot(vector_2d const & other) const -> T {
        return x * other.x + y * other.y;
    }

    constexpr auto cross(vector_2d const & other) const -> T {
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
template <typename T> struct formatter<aoc::math::vector_2d<T>> {
    constexpr auto parse(format_parse_context & ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    auto format(aoc::math::vector_2d<T> const & v, format_context & ctx) const -> decltype(ctx.out()) {
        return format_to(ctx.out(), "({}, {})", v.x, v.y);
    }
};
} // namespace std