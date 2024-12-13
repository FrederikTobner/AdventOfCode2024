#include "../lib/plant_location.hpp"

#include <gtest/gtest.h>

TEST(PlantLocationTest, SplitIntoConnectedLocations) {
    std::unordered_set<aoc::math::vector_2d<int16_t>> locations = {
        {0, 0},
        {0, 1}, // Group 1
        {2, 2},
        {2, 3}, // Group 2
        {4, 4}  // Group 3
    };

    auto groups = aoc::day_12::splitIntoConnectedLocations(locations);
    EXPECT_EQ(groups.size(), 3);

    // Check third group
    EXPECT_TRUE(groups[0].contains({4, 4}));

    // Check second group
    EXPECT_TRUE(groups[1].contains({2, 2}));
    EXPECT_TRUE(groups[1].contains({2, 3}));

    // Check first group
    EXPECT_TRUE(groups[2].contains({0, 0}));
    EXPECT_TRUE(groups[2].contains({0, 1}));
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

    auto price = aoc::day_12::calculateFencePrice(locations);
    EXPECT_EQ(price, 0);

    auto price2 = aoc::day_12::calculateFencePrice2(locations);
    EXPECT_EQ(price2, 0);
}
