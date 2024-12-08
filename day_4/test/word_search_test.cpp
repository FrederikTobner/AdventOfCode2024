#include "../lib/word_search.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc::day_4;
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
    // Arrange
    auto input = "ABC";

    // Act
    auto matches = findWord(grid, input);

    // Assert
    ASSERT_EQ(matches.size(), 1);
    EXPECT_THAT(matches[0].coordinates, ElementsAre(IsPosition(0, 0), IsPosition(0, 1), IsPosition(0, 2)));
}

TEST_F(WordSearchTest, FindsVerticalWord) {
    // Arrange
    auto input = "AFK";

    // Act
    auto matches = findWord(grid, input);

    // Assert
    ASSERT_EQ(matches.size(), 1);
    EXPECT_THAT(matches[0].coordinates, ElementsAre(IsPosition(0, 0), IsPosition(1, 0), IsPosition(2, 0)));
}

TEST_F(WordSearchTest, FindsDiagonalWord) {
    // Arrange
    auto input = "AGM";

    // Act
    auto matches = findWord(grid, input);

    // Assert
    ASSERT_EQ(matches.size(), 1);
    EXPECT_THAT(matches[0].coordinates, ElementsAre(IsPosition(0, 0), IsPosition(1, 1), IsPosition(2, 2)));
}

TEST_F(WordSearchTest, FindsMultipleInstances) {
    // Arrange
    std::vector<std::string_view> repeatingGrid = {"ABA", "BAB", "AAA"};
    auto input = "AAA";

    // Act
    auto matches = findWord(repeatingGrid, input);
    auto matches_size = matches.size();

    // Assert
    ASSERT_EQ(matches_size, 6); // 2 horizontal, 0 vertical, 4 diagonal
}

TEST_F(WordSearchTest, HandlesMissingWord) {
    // Arrange
    auto input = "ZZZ";

    // Act
    auto matches = findWord(grid, input);

    // Assert
    EXPECT_TRUE(matches.empty());
}
