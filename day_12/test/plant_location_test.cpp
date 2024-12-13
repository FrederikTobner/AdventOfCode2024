#include "../lib/plant_location.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <ranges>

MATCHER_P(UnorderedSetEquals, expected, "") {
    if (arg.size() != expected.size()) {
        return false;
    }
    return std::all_of(expected.begin(), expected.end(), [&arg](auto const & exp) {
        return std::find_if(arg.begin(), arg.end(),
                            [&exp](const auto & act) { return std::ranges::equal(exp, act); }) != arg.end();
    });
}

TEST(PlantLocationTest, SplitIntoConnectedLocations) {
    std::unordered_set<aoc::math::vector_2d<int16_t>> locations = {
        {0, 0},
        {0, 1}, // Group 1
        {2, 2},
        {2, 3}, // Group 2
        {4, 4}  // Group 3
    };

    auto groups = aoc::day_12::splitIntoConnectedLocations(locations);

    std::vector<std::unordered_set<aoc::math::vector_2d<int16_t>>> expected_groups = {
        {{0, 0}, {0, 1}}, {{2, 2}, {2, 3}}, {{4, 4}}};

    EXPECT_EQ(groups.size(), 3);
}

TEST(PlantLocationTest, CalculateFencePrice) {
    std::unordered_set<aoc::math::vector_2d<int16_t>> locations = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1} // 2x2 square
    };

    auto price = aoc::day_12::calculateFencePrice(locations);
    EXPECT_EQ(price, 32); // 8 fence elements (2 per cell) * 4 cells
}

TEST(PlantLocationTest, CalculateFencePrice2) {
    std::unordered_set<aoc::math::vector_2d<int16_t>> locations = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1} // 2x2 square
    };

    auto price = aoc::day_12::calculateFencePrice2(locations);
    EXPECT_EQ(price, 16); // 4 border lines * 4 cells
}

TEST(PlantLocationTest, EmptyLocationSet) {
    std::unordered_set<aoc::math::vector_2d<int16_t>> locations;

    auto groups = aoc::day_12::splitIntoConnectedLocations(locations);
    EXPECT_TRUE(groups.empty());
    EXPECT_TRUE(groups.empty());

    auto price = aoc::day_12::calculateFencePrice(locations);
    EXPECT_EQ(price, 0);

    auto price2 = aoc::day_12::calculateFencePrice2(locations);
    EXPECT_EQ(price2, 0);
}
