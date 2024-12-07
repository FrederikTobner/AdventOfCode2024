#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/equation_puzzle_parser.hpp"

using namespace aoc::day_7;

TEST(EquationPuzzleParserTest, ParsesSinglePuzzle) {
    auto puzzles = parsePuzzles("42: 6 7");
    ASSERT_EQ(puzzles.size(), 1);
    EXPECT_EQ(puzzles[0].result.raw(), 42);
    ASSERT_EQ(puzzles[0].values.size(), 2);
    EXPECT_EQ(puzzles[0].values[0], 6);
    EXPECT_EQ(puzzles[0].values[1], 7);
}

TEST(EquationPuzzleParserTest, ParsesMultiplePuzzles) {
    auto puzzles = parsePuzzles("15: 7 8\n42: 6 7");
    ASSERT_EQ(puzzles.size(), 2);

    EXPECT_EQ(puzzles[0].result.raw(), 15);
    ASSERT_EQ(puzzles[0].values.size(), 2);
    EXPECT_EQ(puzzles[0].values[0], 7);
    EXPECT_EQ(puzzles[0].values[1], 8);

    EXPECT_EQ(puzzles[1].result.raw(), 42);
    ASSERT_EQ(puzzles[1].values.size(), 2);
    EXPECT_EQ(puzzles[1].values[0], 6);
    EXPECT_EQ(puzzles[1].values[1], 7);
}

TEST(EquationPuzzleParserTest, HandlesEmptyInput) {
    auto puzzles = parsePuzzles("");
    EXPECT_TRUE(puzzles.empty());
}

TEST(EquationPuzzleParserTest, HandlesWindowsLineEndings) {
    auto puzzles = parsePuzzles("15: 7 8\r\n42: 6 7");
    ASSERT_EQ(puzzles.size(), 2);
    EXPECT_EQ(puzzles[0].result.raw(), 15);
    EXPECT_EQ(puzzles[1].result.raw(), 42);
}

TEST(EquationPuzzleParserTest, HandlesPuzzleWithMultipleValues) {
    auto puzzles = parsePuzzles("142: 1 4 2");
    ASSERT_EQ(puzzles.size(), 1);
    EXPECT_EQ(puzzles[0].result.raw(), 142);
    ASSERT_EQ(puzzles[0].values.size(), 3);
    EXPECT_EQ(puzzles[0].values[0], 1);
    EXPECT_EQ(puzzles[0].values[1], 4);
    EXPECT_EQ(puzzles[0].values[2], 2);
}

TEST(EquationPuzzleParserTest, HandlesExtraWhitespace) {
    auto puzzles = parsePuzzles("42:  6     7  ");
    ASSERT_EQ(puzzles.size(), 1);
    EXPECT_EQ(puzzles[0].result.raw(), 42);
    ASSERT_EQ(puzzles[0].values.size(), 2);
    EXPECT_EQ(puzzles[0].values[0], 6);
    EXPECT_EQ(puzzles[0].values[1], 7);
}