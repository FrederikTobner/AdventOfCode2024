#include "stone.hpp"

#include <cmath>
#include <cstddef>
#include <unordered_map>

#ifdef _DEBUG
#include <chrono>
#endif

#include "../../shared/src/print_compatibility_layer.hpp"

namespace aoc::day_11 {

/// @brief Calculate the number of digits in a number
/// @param num The number to count digits for
/// @return The number of digits in the number
[[nodiscard]] auto getDigitCount(size_t num) noexcept -> size_t {
    return num == 0 ? 1 : static_cast<size_t>(std::log10(num)) + 1;
}

/// @brief Process a single stone according to the rules
/// @param stone The stone to process
/// @param count The number of stones to process
/// @param next The map to store the next iteration's stone counts
[[nodiscard]] static auto processStone(size_t stone, size_t count, std::unordered_map<size_t, size_t> & next) -> void {
    if (stone == 0) {
        next[1] += count;
        return;
    }
    size_t const digits = getDigitCount(stone);
    if (digits % 2 == 0) {
        size_t const half = digits / 2;
        size_t const divisor = static_cast<size_t>(std::pow(10, half));
        next[stone / divisor] += count;
        next[stone % divisor] += count;
    } else {
        next[stone * 2024] += count;
    }
}

/// @brief Update the stone counts for the next iteration
/// @param current The current stone counts
/// @return The updated stone counts for the next iteration
[[nodiscard]] static auto updateStoneCounts(std::unordered_map<size_t, size_t> const & current)
    -> std::unordered_map<size_t, size_t> {
    std::unordered_map<size_t, size_t> next;
    for (auto const & [stone, count] : current) {
        processStone(stone, count, next);
    }
    return next;
}

auto calculateStones(std::vector<size_t> const & stones, size_t const cycles) -> size_t {
#ifdef _DEBUG
    auto const start = std::chrono::high_resolution_clock::now();
#endif

    std::unordered_map<size_t, size_t> stoneCount;
    for (auto const stone : stones) {
        ++stoneCount[stone];
    }

    for (size_t i = 0; i < cycles; ++i) {
        stoneCount = updateStoneCounts(stoneCount);
    }

    size_t totalStones = 0;
    for (auto const & [stone, count] : stoneCount) {
        totalStones += count;
    }

#ifdef _DEBUG
    auto const end = std::chrono::high_resolution_clock::now();
    auto const duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::println("Execution time: {} ms", duration.count());
#endif

    return totalStones;
}

} // namespace aoc::day_11