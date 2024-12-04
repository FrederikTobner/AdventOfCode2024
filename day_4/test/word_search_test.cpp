#include "../lib/word_search.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc::word_search;
using ::testing::AllOf;
using ::testing::ElementsAre;
using ::testing::Field;

MATCHER_P2(IsPosition, row, col, "") {
    return arg.row == row && arg.col == col;
}

class WordSearchTest : public ::testing::Test {
  protected:
    std::vector<std::string_view> grid = {"ABCDE", "FGHIJ", "KLMNO", "PQRST", "UVWXY"};
};

TEST_F(WordSearchTest, FindsHorizontalWord) {
    auto matches = findWord(grid, "ABC");
    ASSERT_EQ(matches.size(), 1);
    EXPECT_THAT(matches[0].coordinates, ElementsAre(IsPosition(0, 0), IsPosition(0, 1), IsPosition(0, 2)));
}

TEST_F(WordSearchTest, FindsVerticalWord) {
    auto matches = findWord(grid, "AFK");
    ASSERT_EQ(matches.size(), 1);
    EXPECT_THAT(matches[0].coordinates, ElementsAre(IsPosition(0, 0), IsPosition(1, 0), IsPosition(2, 0)));
}

TEST_F(WordSearchTest, FindsDiagonalWord) {
    auto matches = findWord(grid, "AGM");
    ASSERT_EQ(matches.size(), 1);
    EXPECT_THAT(matches[0].coordinates, ElementsAre(IsPosition(0, 0), IsPosition(1, 1), IsPosition(2, 2)));
}

TEST_F(WordSearchTest, FindsMultipleInstances) {
    std::vector<std::string_view> repeatingGrid = {"ABA", "BAB", "AAA"};
    auto matches = findWord(repeatingGrid, "AAA");
    ASSERT_EQ(matches.size(), 6); // 2 horizontal, 0 vertical, 4 diagonal
}

TEST_F(WordSearchTest, HandlesMissingWord) {
    auto matches = findWord(grid, "ZZZ");
    EXPECT_TRUE(matches.empty());
}
