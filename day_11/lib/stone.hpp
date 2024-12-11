#pragma once

#include <chrono>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <ranges>
#include <unordered_map>

namespace aoc::day_11 {

size_t getDigitCount(size_t num) {
    if (num == 0) {
        return 1;
    }
    return static_cast<size_t>(std::log10(num)) + 1;
}

template <typename EXECUTION_POLICY>
    requires std::is_execution_policy_v<std::remove_cvref_t<EXECUTION_POLICY>>
size_t calculateStones(std::vector<size_t> const & stones, size_t cycles, EXECUTION_POLICY && policy) {

    auto start = std::chrono::high_resolution_clock::now();

    // Map to store count of stones with same properties
    std::unordered_map<size_t, size_t> stoneCount;

    // Initialize counts
    for (auto stone : stones) {
        stoneCount[stone]++;
    }

    for (size_t i = 0; i < cycles; i++) {

        std::unordered_map<size_t, size_t> nextCount;

        for (auto const & [stone, count] : stoneCount) {
            if (stone == 0) {
                // Zeros become ones
                nextCount[1] += count;
            } else {
                size_t digits = getDigitCount(stone);
                if (digits % 2 == 0) {
                    // Split number into two parts
                    size_t half = digits / 2;
                    size_t divisor = static_cast<size_t>(std::pow(10, half));
                    size_t left = stone / divisor;
                    size_t right = stone % divisor;
                    // Each stone splits into two
                    nextCount[left] += count;
                    nextCount[right] += count;
                } else {
                    // Multiply by 2024
                    nextCount[stone * 2024] += count;
                }
            }
        }

        stoneCount = std::move(nextCount);
    }

    // Sum up all stone counts
    size_t totalStones = 0;
    for (auto const & [stone, count] : stoneCount) {
        totalStones += count;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::println("Execution time: {} ms", duration.count());

    return totalStones;
}

} // namespace aoc::day_11