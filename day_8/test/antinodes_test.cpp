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
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {0, 0}}, {'1', {2, 2}}};

    auto result = aoc::day_8::findDiscreteAntinodes(5, 5, antenas);

    EXPECT_THAT(result, testing::UnorderedElementsAre(aoc::day_8::coordinate{4, 4}));
}

TEST_F(AntinodesTest, DiscreteAntinodesMultipleFrequencies) {
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {0, 0}}, {'1', {2, 2}}, {'2', {1, 1}}, {'2', {3, 3}}};

    auto result = aoc::day_8::findDiscreteAntinodes(6, 6, antenas);

    EXPECT_THAT(result, testing::UnorderedElementsAre(aoc::day_8::coordinate{4, 4}, aoc::day_8::coordinate{5, 5}));
}

TEST_F(AntinodesTest, ContinuousAntinodesSimplePattern) {
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {0, 0}}, {'1', {1, 1}}};

    auto result = aoc::day_8::findContinousAntinodes(4, 4, antenas);

    EXPECT_THAT(result, testing::UnorderedElementsAre(aoc::day_8::coordinate{0, 0}, aoc::day_8::coordinate{1, 1},
                                                      aoc::day_8::coordinate{2, 2}, aoc::day_8::coordinate{3, 3}));
}

TEST_F(AntinodesTest, EmptyAntenasReturnsEmptySet) {
    std::multimap<char, aoc::day_8::coordinate> antenas;

    auto discrete_result = aoc::day_8::findDiscreteAntinodes(5, 5, antenas);
    auto continuous_result = aoc::day_8::findContinousAntinodes(5, 5, antenas);

    EXPECT_TRUE(discrete_result.empty());
    EXPECT_TRUE(continuous_result.empty());
}

TEST_F(AntinodesTest, OutOfBoundsAntinodesAreFiltered) {
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {0, 0}}, {'1', {3, 3}}};

    auto result = aoc::day_8::findDiscreteAntinodes(4, 4, antenas);

    EXPECT_TRUE(result.empty());
}

TEST_F(AntinodesTest, SingleAntennaHasNoAntinodes) {
    std::multimap<char, aoc::day_8::coordinate> antenas{{'1', {2, 2}}};

    auto discrete_result = aoc::day_8::findDiscreteAntinodes(5, 5, antenas);
    auto continuous_result = aoc::day_8::findContinousAntinodes(5, 5, antenas);

    EXPECT_TRUE(discrete_result.empty());
    EXPECT_TRUE(continuous_result.empty());
}
