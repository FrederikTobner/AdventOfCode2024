#include "../lib/calculations.hpp"

#include <gtest/gtest.h>

#include <cstdint>
#include <utility>
#include <vector>

TEST(Calculations, AcumulateProductsOfPairs) {
    std::vector<std::pair<uint16_t, uint16_t>> matches{{2, 4}, {3, 7}, {5, 5}, {11, 8}, {8, 5}};

    auto result = aoc::day_3::accumulateProducts(matches);
    uint64_t expected = 2 * 4 + 3 * 7 + 5 * 5 + 11 * 8 + 8 * 5;
    EXPECT_EQ(result, expected);
}