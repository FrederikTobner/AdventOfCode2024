#pragma once

#include <cmath>
#include <concepts>
#include <format>
#include <string>
#include <string_view>

namespace aoc::math {
template <typename T = float>
    requires std::is_arithmetic_v<T>
class vector_3d {
  public:
    T x;
    T y;
    T z;

    constexpr vector_3d() : x(0), y(0), z(0) {
    }
    constexpr vector_3d(T x, T y, T z) : x(x), y(y), z(z) {
    }

    constexpr auto operator+(vector_3d const & other) const -> vector_3d {
        return vector_3d(x + other.x, y + other.y, z + other.z);
    }

    constexpr auto operator-(vector_3d const & other) const -> vector_3d {
        return vector_3d(x - other.x, y - other.y, z - other.z);
    }

    constexpr auto operator*(T scalar) const -> vector_3d {
        return vector_3d(x * scalar, y * scalar, z * scalar);
    }

    constexpr auto operator/(T scalar) const -> vector_3d {
        return vector_3d(x / scalar, y / scalar, z / scalar);
    }

    constexpr auto operator==(vector_3d const & other) const -> bool {
        return x == other.x && y == other.y && z == other.z;
    }

    constexpr auto operator!=(vector_3d const & other) const -> bool {
        return !(*this == other);
    }

    constexpr auto operator+=(vector_3d const & other) -> vector_3d & {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    constexpr auto operator-=(vector_3d const & other) -> vector_3d & {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    constexpr auto operator*=(T scalar) -> vector_3d & {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    constexpr auto operator/=(T scalar) -> vector_3d & {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    auto magnitude() const -> T {
        return std::sqrt(x * x + y * y + z * z);
    }

    auto normalize() -> vector_3d & {
        T mag = magnitude();
        if (mag != 0) {
            *this /= mag;
        }
        return *this;
    }
};
} // namespace aoc::math

namespace std {
template <typename T> struct hash<aoc::math::vector_3d<T>> {
    auto operator()(aoc::math::vector_3d<T> const & v) const -> size_t {
        return hash<T>{}(v.x) ^ hash<T>{}(v.y) ^ hash<T>{}(v.z);
    }
};

template <typename T> struct formatter<aoc::math::vector_3d<T>> {
    constexpr auto parse(format_parse_context & ctx) -> decltype(ctx.begin()) {
        return ctx.begin();
    }

    auto format(aoc::math::vector_3d<T> const & v, format_context & ctx) const -> decltype(ctx.out()) {
        return format_to(ctx.out(), "({}, {}, {})", v.x, v.y, v.z);
    }
};
} // namespace std