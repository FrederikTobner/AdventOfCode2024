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
    std::vector<aoc::day_4::match> matches{createMatch({{0, 0}, {1, 1}, {2, 2}}),
                                           createMatch({{1, 1}, {2, 2}, {3, 3}})};
    EXPECT_EQ(aoc::day_4::countOverlappingDiagonal(matches), 0);
}

TEST_F(MatchFilterTest, TwoOverlappingMatches) {
    std::vector<aoc::day_4::match> matches{createMatch({{0, 0}, {1, 1}, {2, 2}}),
                                           createMatch({{2, 2}, {1, 1}, {0, 0}})};
    EXPECT_EQ(aoc::day_4::countOverlappingDiagonal(matches), 1);
}

TEST_F(MatchFilterTest, NonDiagonalMatchesIgnored) {
    std::vector<aoc::day_4::match> matches{
        createMatch({{0, 0}, {0, 1}, {0, 2}}), // horizontal
        createMatch({{0, 0}, {1, 0}, {2, 0}})  // vertical
    };
    EXPECT_EQ(aoc::day_4::countOverlappingDiagonal(matches), 0);
}

TEST_F(MatchFilterTest, EmptyMatchList) {
    std::vector<aoc::day_4::match> matches;
    EXPECT_EQ(aoc::day_4::countOverlappingDiagonal(matches), 0);
}