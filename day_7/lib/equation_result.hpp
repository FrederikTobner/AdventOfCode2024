#pragma once

#include <concepts>
#include <cstddef>

namespace aoc::day_7 {

/// Represents a wrapped numeric value with custom arithmetic operations
/// @tparam T The underlying numeric type used for calculations (defaults to size_t)
template <typename T = size_t>
    requires std::integral<T>
class equation_result {
    T val_;

  public:
    /// Constructs a new equation result
    /// @param v The value to wrap
    constexpr explicit equation_result(T v) : val_(v) {
    }

    /// Gets the raw underlying value
    /// @return The wrapped value
    [[nodiscard]] constexpr T getRawValue() const {
        return val_;
    }

    /// Adds two equation results
    /// @param lhs Left-hand operand
    /// @param rhs Right-hand operand
    /// @return New equation result containing the sum
    friend equation_result operator+(equation_result lhs, equation_result rhs) {
        return equation_result{lhs.val_ + rhs.val_};
    }

    /// Multiplies two equation results
    /// @param lhs Left-hand operand
    /// @param rhs Right-hand operand
    /// @return New equation result containing the product
    friend equation_result operator*(equation_result lhs, equation_result rhs) {
        return equation_result{lhs.val_ * rhs.val_};
    }

    /// Concatenates two equation results as digits
    /// @param lhs Left-hand operand
    /// @param rhs Right-hand operand
    /// @return New equation result containing the concatenated number
    friend equation_result operator|(equation_result lhs, equation_result rhs) {
        T multiplier = 10;
        T temp = rhs.val_;
        while (temp >= 10) {
            multiplier *= 10;
            temp /= 10;
        }
        return equation_result{lhs.val_ * multiplier + rhs.val_};
    }

    /// @brief Compares two equation results for equality
    /// @param lhs The left-hand operand
    /// @param rhs The right-hand operand
    /// @return true if the two equation results are equal
    friend bool operator==(equation_result lhs, equation_result rhs) {
        return lhs.val_ == rhs.val_;
    }

    /// @brief Compares two equation results and checks if the left-hand operand is less than the right-hand operand
    /// @param lhs The left-hand operand
    /// @param rhs The right-hand operand
    /// @return true if the left-hand operand is less than the right-hand operand
    friend bool operator<(equation_result lhs, equation_result rhs) {
        return lhs.val_ < rhs.val_;
    }

    /// @brief Compares two equation results and checks if the left-hand operand is greater than the right-hand operand
    /// @param lhs The left-hand operand
    /// @param rhs The right-hand operand
    /// @return true if the left-hand operand is greater than the right-hand operand
    friend bool operator>(equation_result lhs, equation_result rhs) {
        return lhs.val_ > rhs.val_;
    }
};
} // namespace aoc::day_7