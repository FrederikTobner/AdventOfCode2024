#include "../lib/calculations.hpp"

#include <gtest/gtest.h>

TEST(CalculationsTest, CalculateTotalPriceWithoutIncrement) {
    auto result = aoc::day_13::calculateTotalPrice(
        {"Button A: X+94, Y+34", "Button B : X+22, Y+67", "Prize : X=8400, Y=5400 "}, 0);
    EXPECT_EQ(result, 280);
}

TEST(CalculationsTest, CalculateTotalPriceWitIncrementNotSolvable) {
    // Can not be solved
    auto result = aoc::day_13::calculateTotalPrice(
        {"Button A: X+94, Y+34", "Button B : X+22, Y+67", "Prize : X=8400, Y=5400 "}, 10000000000000);
    EXPECT_EQ(result, 0);
}

TEST(CalculationsTest, CalculateTotalPriceWitIncrementSolvable) {
    // Can not be solved
    auto result = aoc::day_13::calculateTotalPrice(
        {"Button A: X+26, Y+66", "Button B : X+67, Y+21", "Prize : X = 12748, Y = 12176"}, 10000000000000);
    EXPECT_EQ(result, 459236326669);
}
