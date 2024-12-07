#pragma once

#include <cstddef>

namespace aoc::day_7 {

template <typename T = size_t> class equation_result {
    T val_;

  public:
    constexpr explicit equation_result(T v) : val_(v) {
    }
    [[nodiscard]] constexpr T raw() const {
        return val_;
    }

    friend equation_result operator+(equation_result lhs, equation_result rhs) {
        return equation_result{lhs.val_ + rhs.val_};
    }

    friend equation_result operator*(equation_result lhs, equation_result rhs) {
        return equation_result{lhs.val_ * rhs.val_};
    }

    friend equation_result operator|(equation_result lhs, equation_result rhs) {
        T multiplier = 10;
        T temp = rhs.val_;
        while (temp >= 10) {
            multiplier *= 10;
            temp /= 10;
        }
        return equation_result{lhs.val_ * multiplier + rhs.val_};
    }

    friend bool operator==(equation_result lhs, equation_result rhs) {
        return lhs.val_ == rhs.val_;
    }
};
} // namespace aoc::day_7