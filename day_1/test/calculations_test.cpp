#include "../lib/calculations.hpp"

#include <gtest/gtest.h>

TEST(Calculations, TotalDistance) {
    // Arrange
    std::multiset<int64_t> leftList{3, 4, 2, 1, 3, 3};
    std::multiset<int64_t> rightList{4, 3, 5, 3, 9, 3};

    // Act
    auto result = aoc::day_1::totalDistance(leftList, rightList);

    // Assert
    EXPECT_EQ(result, 11);
}

TEST(Calculations, SimilarityScore) {
    // Arrange
    std::multiset<int64_t> leftList{3, 4, 2, 1, 3, 3};
    std::multiset<int64_t> rightList{4, 3, 5, 3, 9, 3};

    // Act
    auto result = aoc::day_1::similarityScore(leftList, rightList);

    // Assert
    EXPECT_EQ(result, 31);
}