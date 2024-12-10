#pragma once

#include <cmath>
#include <concepts>

namespace aoc::math {
template <typename T = float>
    requires std::is_arithmetic_v<T>
class vector_3d {
  public:
    T x;
    T y;
    T z;

    vector_3d() : x(0), y(0), z(0) {
    }
    vector_3d(T x, T y, T z) : x(x), y(y), z(z) {
    }

    auto operator+(vector_3d const & other) const -> vector_3d {
        return vector_3d(x + other.x, y + other.y, z + other.z);
    }

    auto operator-(vector_3d const & other) const -> vector_3d {
        return vector_3d(x - other.x, y - other.y, z - other.z);
    }

    auto operator*(T scalar) const -> vector_3d {
        return vector_3d(x * scalar, y * scalar, z * scalar);
    }

    auto operator/(T scalar) const -> vector_3d {
        return vector_3d(x / scalar, y / scalar, z / scalar);
    }

    auto operator==(vector_3d const & other) const -> bool {
        return x == other.x && y == other.y && z == other.z;
    }

    auto operator!=(vector_3d const & other) const -> bool {
        return !(*this == other);
    }

    auto operator+=(vector_3d const & other) -> vector_3d & {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    auto operator-=(vector_3d const & other) -> vector_3d & {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    auto operator*=(T scalar) -> vector_3d & {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    auto operator/=(T scalar) -> vector_3d & {
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