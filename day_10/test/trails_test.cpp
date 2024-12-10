#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/trails.hpp"

using namespace aoc::day_10;
using namespace aoc::tree;
using namespace aoc::math;

class TrailsTest : public ::testing::Test {
  protected:
    // Helper method to create a simple linear path
    tree_node<aoc::math::vector_3d<uint8_t>> createLinearPath() {
        return tree_node<aoc::math::vector_3d<uint8_t>>{{0, 0, 0}, {{{0, 1, 1}, {{{0, 2, 2}, {{{0, 3, 9}, {}}}}}}}};
    }

    // Helper method to create a path with two branches
    tree_node<aoc::math::vector_3d<uint8_t>> createBranchingPath() {
        return tree_node<aoc::math::vector_3d<uint8_t>>{{0, 0, 0},
                                                        {{{1, 0, 1}, {{{2, 0, 2}, {{{3, 0, 9}, {}}}}, {{2, 1, 9}, {}}}},
                                                         {{0, 1, 1}, {{{0, 2, 2}, {{{0, 3, 9}, {}}}}}}}};
    }
};

class TrailEndValueTest : public testing::TestWithParam<std::tuple<uint8_t, bool>> {};

TEST_P(TrailEndValueTest, IsTrailEndParameterized) {
    // Arrange
    auto [value, expected] = GetParam();

    // Act
    auto result = isTrailEnd(value);

    // Assert
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(TrailEnds, TrailEndValueTest,
                         testing::Values(std::make_tuple(9, true), std::make_tuple(0, false),
                                         std::make_tuple(5, false)));

class TrailStartValueTest : public testing::TestWithParam<std::tuple<uint8_t, bool>> {};

TEST_P(TrailStartValueTest, IsTrailStartParameterized) {
    // Arrange
    auto [value, expected] = GetParam();

    // Act
    auto result = isTrailStart(value);

    // Assert
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(TrailStarts, TrailStartValueTest,
                         testing::Values(std::make_tuple(0, true), std::make_tuple(9, false),
                                         std::make_tuple(5, false)));

TEST_F(TrailsTest, CalculateUniquePathsLinear) {
    // Arrange
    std::vector<tree_node<aoc::math::vector_3d<uint8_t>>> nodes{createLinearPath()};
    trails test_trails(nodes);

    // Act
    auto result = test_trails.calculateUniquePaths();

    // Assert
    EXPECT_EQ(result, 1);
}

TEST_F(TrailsTest, CalculateUniquePathsBranching) {
    // Arrange
    std::vector<tree_node<aoc::math::vector_3d<uint8_t>>> nodes{createBranchingPath()};
    trails test_trails(nodes);

    // Act
    auto result = test_trails.calculateUniquePaths();

    // Assert
    EXPECT_EQ(result, 3);
}

TEST_F(TrailsTest, CalculateRatingLinear) {
    // Arrange
    std::vector<tree_node<aoc::math::vector_3d<uint8_t>>> nodes{createLinearPath()};
    trails test_trails(nodes);

    // Act
    auto result = test_trails.calculateRating();

    // Assert
    EXPECT_EQ(result, 1);
}

TEST_F(TrailsTest, CalculateRatingBranching) {
    // Arrange
    std::vector<tree_node<aoc::math::vector_3d<uint8_t>>> nodes{createBranchingPath()};
    trails test_trails(nodes);

    // Act
    auto result = test_trails.calculateRating();

    // Assert
    EXPECT_EQ(result, 3);
}