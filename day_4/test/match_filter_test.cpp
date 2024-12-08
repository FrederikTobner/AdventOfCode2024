#include "../lib/match_filter.hpp"

#include <gtest/gtest.h>

#include "../lib/match_filter.hpp"
#include <gtest/gtest.h>

class MatchFilterTest : public ::testing::Test {
  protected:
    // Helper function to create a match with given positions
    static auto createMatch(std::vector<std::pair<size_t, size_t>> positions) {
        aoc::day_4::match match;
        for (auto [row, col] : positions) {
            match.coordinates.push_back({row, col});
        }
        return match;
    }
};

TEST_F(MatchFilterTest, NoOverlappingMatches) {
    // Arrange
    std::vector<aoc::day_4::match> matches{createMatch({{0, 0}, {1, 1}, {2, 2}}),
                                           createMatch({{1, 1}, {2, 2}, {3, 3}})};
    // Act
    auto result = aoc::day_4::countOverlappingDiagonal(matches);

    // Assert
    EXPECT_EQ(result, 0);
}

TEST_F(MatchFilterTest, TwoOverlappingMatches) {
    // Arrange
    std::vector<aoc::day_4::match> matches{createMatch({{0, 0}, {1, 1}, {2, 2}}),
                                           createMatch({{2, 2}, {1, 1}, {0, 0}})};

    // Act
    auto result = aoc::day_4::countOverlappingDiagonal(matches);

    // Assert
    EXPECT_EQ(result, 1);
}

TEST_F(MatchFilterTest, NonDiagonalMatchesIgnored) {
    // Arrange
    std::vector<aoc::day_4::match> matches{
        createMatch({{0, 0}, {0, 1}, {0, 2}}), // horizontal
        createMatch({{0, 0}, {1, 0}, {2, 0}})  // vertical
    };

    // Act
    auto result = aoc::day_4::countOverlappingDiagonal(matches);

    // Assert
    EXPECT_EQ(result, 0);
}

TEST_F(MatchFilterTest, EmptyMatchList) {
    // Arrange
    std::vector<aoc::day_4::match> matches;

    // Act
    auto result = aoc::day_4::countOverlappingDiagonal(matches);

    // Assert
    EXPECT_EQ(result, 0);
}