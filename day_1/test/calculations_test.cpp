#include "../lib/calculations.hpp"

#include <gtest/gtest.h>

TEST(Calculations, TotalDistance) {
    std::multiset<int64_t> leftList{3, 4, 2, 1, 3, 3};
    std::multiset<int64_t> rightList{4, 3, 5, 3, 9, 3};

    auto result = aoc::day_1::totalDistance(leftList, rightList);
    EXPECT_EQ(result, 11);
}

TEST(Calculations, SimilarityScore) {
    std::multiset<int64_t> leftList{3, 4, 2, 1, 3, 3};
    std::multiset<int64_t> rightList{4, 3, 5, 3, 9, 3};

    auto result = aoc::day_1::similarityScore(leftList, rightList);
    EXPECT_EQ(result, 31);
}