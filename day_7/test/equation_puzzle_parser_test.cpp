#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/equation_puzzle_parser.hpp"

using namespace aoc::day_7;

TEST(EquationPuzzleParserTest, ParsesSinglePuzzle) {
    auto puzzles = parsePuzzles("42: 6 7");
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    ASSERT_EQ(puzzleExtracted.size(), 1);
    EXPECT_EQ(puzzleExtracted[0].result.getRawValue(), 42);
    ASSERT_EQ(puzzleExtracted[0].values.size(), 2);
    EXPECT_EQ(puzzleExtracted[0].values[0], 6);
    EXPECT_EQ(puzzleExtracted[0].values[1], 7);
}

TEST(EquationPuzzleParserTest, ParsesMultiplePuzzles) {
    auto puzzles = parsePuzzles("15: 7 8\n42: 6 7");
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    ASSERT_EQ(puzzleExtracted.size(), 2);

    EXPECT_EQ(puzzleExtracted[0].result.getRawValue(), 15);
    ASSERT_EQ(puzzleExtracted[0].values.size(), 2);
    EXPECT_EQ(puzzleExtracted[0].values[0], 7);
    EXPECT_EQ(puzzleExtracted[0].values[1], 8);

    EXPECT_EQ(puzzleExtracted[1].result.getRawValue(), 42);
    ASSERT_EQ(puzzleExtracted[1].values.size(), 2);
    EXPECT_EQ(puzzleExtracted[1].values[0], 6);
    EXPECT_EQ(puzzleExtracted[1].values[1], 7);
}

TEST(EquationPuzzleParserTest, HandlesEmptyInput) {
    auto puzzles = parsePuzzles("");
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    EXPECT_TRUE(puzzleExtracted.empty());
}

TEST(EquationPuzzleParserTest, HandlesWindowsLineEndings) {
    auto puzzles = parsePuzzles("15: 7 8\r\n42: 6 7");
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    ASSERT_EQ(puzzleExtracted.size(), 2);
    EXPECT_EQ(puzzleExtracted[0].result.getRawValue(), 15);
    EXPECT_EQ(puzzleExtracted[1].result.getRawValue(), 42);
}

TEST(EquationPuzzleParserTest, HandlesPuzzleWithMultipleValues) {
    auto puzzles = parsePuzzles("142: 1 4 2");
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    ASSERT_EQ(puzzleExtracted.size(), 1);
    EXPECT_EQ(puzzleExtracted[0].result.getRawValue(), 142);
    ASSERT_EQ(puzzleExtracted[0].values.size(), 3);
    EXPECT_EQ(puzzleExtracted[0].values[0], 1);
    EXPECT_EQ(puzzleExtracted[0].values[1], 4);
    EXPECT_EQ(puzzleExtracted[0].values[2], 2);
}

TEST(EquationPuzzleParserTest, HandlesExtraWhitespace) {
    auto puzzles = parsePuzzles("42:  6     7  ");
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    ASSERT_EQ(puzzleExtracted.size(), 1);
    EXPECT_EQ(puzzleExtracted[0].result.getRawValue(), 42);
    ASSERT_EQ(puzzleExtracted[0].values.size(), 2);
    EXPECT_EQ(puzzleExtracted[0].values[0], 6);
    EXPECT_EQ(puzzleExtracted[0].values[1], 7);
}