#pragma once

#include <cmath>
#include <cstdint>
#include <vector>

namespace aoc::day_17 {

int64_t calculateByte(int64_t n) {
    auto b = n % 8;
    b ^= 7;
    auto c = n / static_cast<int64_t>(std::pow(2, b));
    b ^= c;
    b ^= 7;
    return b % 8;
}

int64_t findDesiredRegisterValue(int64_t desired_register_value, std::vector<int64_t> const & goals, int currentIndex) {
    for (int i = 0; i < 8; i++) {
        if (calculateByte(desired_register_value + i) == goals[currentIndex]) {
            if (currentIndex + 1 == goals.size()) {
                return desired_register_value;
            }
            int64_t result = findDesiredRegisterValue((desired_register_value + i) << 3, goals, currentIndex + 1);
            if (result != -1) {
                return result;
            }
        }
    }
    return -1;
}

auto convertModifiedOctal(int64_t a) -> std::vector<int64_t> {
    std::vector<int64_t> result;
    do {
        auto b = a % 8;
        b = b ^ 7;
        auto c = a / static_cast<int64_t>(std::pow(2, b));
        a = a / 8;
        b = b ^ c;
        b = b ^ 7;
        result.push_back(b % 8);
    } while (a != 0);
    return result;
}

} // namespace aoc::day_17