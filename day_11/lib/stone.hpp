#pragma once

#include <chrono>
#include <concepts>
#include <cstddef>
#include <ranges>

#include "../../shared/src/print_compatibility_layer.hpp"

namespace aoc::day_11 {

/*ording to the first applicable rule in this list:
If the stone is engraved with the number 0, it is replaced by a stone engraved with the number 1.
If the stone is engraved with a number that has an even number of digits, it is replaced by two stones. The left
half of the digits are engraved on the new left stone, and the right half of the digits are engraved on the new
right stone. (The new numbers don't keep extra leading zeroes: 1000 would become stones 10 and 0.) If none of the
other rules apply, the stone is replaced by a new stone; the old stone's number multiplied by 2024 is engraved on
the new stone.*/
void onBlink(size_t index, std::vector<std::vector<size_t>> & stonesFragmented) {
    auto & stone = stonesFragmented[index];
    if (stone[0] == 0) {
        stone[0] = 1;
    } else {
        auto digits = 0;
        auto temp = stone[0];
        while (temp) {
            temp /= 10;
            digits++;
        }
        if (digits % 2 == 0) {
            auto half = digits / 2;
            auto left = stone[0] / static_cast<int>(std::pow(10, half));
            auto right = stone[0] % static_cast<int>(std::pow(10, half));
            stone[0] = left;
            // Insert the right stone after the current stone
            auto newFragment = std::vector<size_t>{right};
            stonesFragmented.emplace_back(newFragment);
        } else {
            stone[0] *= 2024;
        }
    }
}

size_t calculateStones(std::vector<size_t> & stones, size_t cycles) {
    std::vector<std::vector<size_t>> stonesFragmented;

    for (auto stone : stones) {
        std::vector<size_t> stoneFragment;
        stoneFragment.push_back(stone);
        stonesFragmented.push_back(stoneFragment);
    }

    for (size_t i = 0; i < cycles; i++) {
        // Measure the time taken to process each cycle
        auto start = std::chrono::high_resolution_clock::now();
        size_t current_size = stonesFragmented.size();
        for (size_t j = 0; j < current_size; j++) {
            onBlink(j, stonesFragmented);
        }
        auto end = std::chrono::high_resolution_clock::now();
        std::println("Cycle {} took {} ms to execute", i,
                     std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());
    }

    size_t result_size = 0;
    for (auto & stoneFragment : stonesFragmented) {
        result_size += stoneFragment.size();
    }
    return result_size;
}

} // namespace aoc::day_11