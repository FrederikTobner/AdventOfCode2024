#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/antinodes.hpp"

class AntinodesTest : public ::testing::Test {
  protected:
    void SetUp() override {
        // Common test setup
    }
};

TEST_F(AntinodesTest, DiscreteAntinodesSimplePattern) {
    // Arrange
    std::multimap<char, aoc::math::Vector2D<int64_t>> antenas{{'1', {0, 0}}, {'1', {2, 2}}};

    // Act
    auto result = aoc::day_8::findDiscreteAntinodes(5, 5, antenas);

    // Assert
    EXPECT_THAT(result, testing::UnorderedElementsAre(aoc::math::Vector2D<int64_t>{4, 4}));
}

TEST_F(AntinodesTest, DiscreteAntinodesMultipleFrequencies) {
    // Arrange
    std::multimap<char, aoc::math::Vector2D<int64_t>> antenas{
        {'1', {0, 0}}, {'1', {2, 2}}, {'2', {1, 1}}, {'2', {3, 3}}};

    // Act
    auto result = aoc::day_8::findDiscreteAntinodes(6, 6, antenas);

    // Assert
    EXPECT_THAT(result,
                testing::UnorderedElementsAre(aoc::math::Vector2D<int64_t>{4, 4}, aoc::math::Vector2D<int64_t>{5, 5}));
}

TEST_F(AntinodesTest, ContinuousAntinodesSimplePattern) {
    // Arrange
    std::multimap<char, aoc::math::Vector2D<int64_t>> antenas{{'1', {0, 0}}, {'1', {1, 1}}};

    // Act
    auto result = aoc::day_8::findContinousAntinodes(4, 4, antenas);

    // Assert
    EXPECT_THAT(result,
                testing::UnorderedElementsAre(aoc::math::Vector2D<int64_t>{0, 0}, aoc::math::Vector2D<int64_t>{1, 1},
                                              aoc::math::Vector2D<int64_t>{2, 2}, aoc::math::Vector2D<int64_t>{3, 3}));
}

TEST_F(AntinodesTest, EmptyAntenasReturnsEmptySet) {
    // Arrange
    std::multimap<char, aoc::math::Vector2D<int64_t>> antenas;

    // Act
    auto discrete_result = aoc::day_8::findDiscreteAntinodes(5, 5, antenas);
    auto continuous_result = aoc::day_8::findContinousAntinodes(5, 5, antenas);

    // Assert
    EXPECT_TRUE(discrete_result.empty());
    EXPECT_TRUE(continuous_result.empty());
}

TEST_F(AntinodesTest, OutOfBoundsAntinodesAreFiltered) {
    // Arrange
    std::multimap<char, aoc::math::Vector2D<int64_t>> antenas{{'1', {0, 0}}, {'1', {3, 3}}};

    // Act
    auto result = aoc::day_8::findDiscreteAntinodes(4, 4, antenas);

    // Assert
    EXPECT_TRUE(result.empty());
}

TEST_F(AntinodesTest, SingleAntennaHasNoAntinodes) {
    // Arrange
    std::multimap<char, aoc::math::Vector2D<int64_t>> antenas{{'1', {2, 2}}};

    // Act
    auto discrete_result = aoc::day_8::findDiscreteAntinodes(5, 5, antenas);
    auto continuous_result = aoc::day_8::findContinousAntinodes(5, 5, antenas);

    // Assert
    EXPECT_TRUE(discrete_result.empty());
    EXPECT_TRUE(continuous_result.empty());
}
