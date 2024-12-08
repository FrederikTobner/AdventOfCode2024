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
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {0, 0}}, {'1', {2, 2}}};

    // Act
    auto result = aoc::day_8::findDiscreteAntinodes(5, 5, antenas);

    // Assert
    EXPECT_THAT(result, testing::UnorderedElementsAre(aoc::day_8::coordinate{4, 4}));
}

TEST_F(AntinodesTest, DiscreteAntinodesMultipleFrequencies) {
    // Arrange
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {0, 0}}, {'1', {2, 2}}, {'2', {1, 1}}, {'2', {3, 3}}};

    // Act
    auto result = aoc::day_8::findDiscreteAntinodes(6, 6, antenas);

    // Assert
    EXPECT_THAT(result, testing::UnorderedElementsAre(aoc::day_8::coordinate{4, 4}, aoc::day_8::coordinate{5, 5}));
}

TEST_F(AntinodesTest, ContinuousAntinodesSimplePattern) {
    // Arrange
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {0, 0}}, {'1', {1, 1}}};

    // Act
    auto result = aoc::day_8::findContinousAntinodes(4, 4, antenas);

    // Assert
    EXPECT_THAT(result, testing::UnorderedElementsAre(aoc::day_8::coordinate{0, 0}, aoc::day_8::coordinate{1, 1},
                                                      aoc::day_8::coordinate{2, 2}, aoc::day_8::coordinate{3, 3}));
}

TEST_F(AntinodesTest, EmptyAntenasReturnsEmptySet) {
    // Arrange
    std::multimap<char, aoc::day_8::coordinate> antenas;

    // Act
    auto discrete_result = aoc::day_8::findDiscreteAntinodes(5, 5, antenas);
    auto continuous_result = aoc::day_8::findContinousAntinodes(5, 5, antenas);

    // Assert
    EXPECT_TRUE(discrete_result.empty());
    EXPECT_TRUE(continuous_result.empty());
}

TEST_F(AntinodesTest, OutOfBoundsAntinodesAreFiltered) {
    // Arrange
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {0, 0}}, {'1', {3, 3}}};

    // Act
    auto result = aoc::day_8::findDiscreteAntinodes(4, 4, antenas);

    // Assert
    EXPECT_TRUE(result.empty());
}

TEST_F(AntinodesTest, SingleAntennaHasNoAntinodes) {
    // Arrange
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {2, 2}}};

    // Act
    auto discrete_result = aoc::day_8::findDiscreteAntinodes(5, 5, antenas);
    auto continuous_result = aoc::day_8::findContinousAntinodes(5, 5, antenas);

    // Assert
    EXPECT_TRUE(discrete_result.empty());
    EXPECT_TRUE(continuous_result.empty());
}
