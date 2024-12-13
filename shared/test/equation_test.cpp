#include "../src/equation.hpp"

#include <gtest/gtest.h>

#include <cstdint>

TEST(EquationTest, SolveEquationsWithTwoUnknows) {
    auto result = aoc::math::solveEquationsWithTwoUnknows({7, 2}, {2, 1}, {11, 4});
    ASSERT_TRUE(result.has_value());
    EXPECT_EQ(result->first, 1);
    EXPECT_EQ(result->second, 2);
}

TEST(EquationTest, SolveEquationsWithTwoUnknows_NoSolution) {
    auto result = aoc::math::solveEquationsWithTwoUnknows({1, 2}, {3, 4}, {5, 7});
    EXPECT_FALSE(result.has_value());
}

TEST(EquationTest, SolveEquationsWithTwoUnknows_NegativeSolution) {
    auto result = aoc::math::solveEquationsWithTwoUnknows({1, 2}, {3, 4}, {2, 2});
    EXPECT_FALSE(result.has_value());
}

TEST(EquationTest, SolveEquationsWithTwoUnknows_FractionalSolution) {
    auto result = aoc::math::solveEquationsWithTwoUnknows({1, 2}, {3, 4}, {5, 7});
    EXPECT_FALSE(result.has_value());
}