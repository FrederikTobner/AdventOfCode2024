#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../lib/equation_puzzle_parser.hpp"

using namespace aoc::day_7;

TEST(EquationPuzzleParserTest, ParsesSinglePuzzle) {
    // Arrange
    auto input = "42: 6 7";

    // Act
    auto puzzles = parsePuzzles(input);

    // Assert
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    ASSERT_EQ(puzzleExtracted.size(), 1);
    EXPECT_EQ(puzzleExtracted[0].result.getRawValue(), 42);
    ASSERT_EQ(puzzleExtracted[0].values.size(), 2);
    EXPECT_EQ(puzzleExtracted[0].values[0], 6);
    EXPECT_EQ(puzzleExtracted[0].values[1], 7);
}

TEST(EquationPuzzleParserTest, ParsesMultiplePuzzles) {
    // Arrange
    auto input = "15: 7 8\n42: 6 7";

    // Act
    auto puzzles = parsePuzzles(input);

    // Assert
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
    // Arrange
    auto input = "";

    // Act
    auto puzzles = parsePuzzles(input);

    // Assert
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    EXPECT_TRUE(puzzleExtracted.empty());
}

TEST(EquationPuzzleParserTest, HandlesWindowsLineEndings) {
    // Arrange
    auto input = "15: 7 8\r\n42: 6 7";

    // Act
    auto puzzles = parsePuzzles(input);

    // Assert
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    ASSERT_EQ(puzzleExtracted.size(), 2);
    EXPECT_EQ(puzzleExtracted[0].result.getRawValue(), 15);
    EXPECT_EQ(puzzleExtracted[1].result.getRawValue(), 42);
}

TEST(EquationPuzzleParserTest, HandlesPuzzleWithMultipleValues) {
    // Arrange
    auto input = "142: 1 4 2";

    // Act
    auto puzzles = parsePuzzles(input);

    // Assert
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
    // Arrange
    auto input = "42:  6     7  ";

    // Act
    auto puzzles = parsePuzzles(input);

    // Assert
    ASSERT_TRUE(puzzles);
    auto puzzleExtracted = *puzzles;
    ASSERT_EQ(puzzleExtracted.size(), 1);
    EXPECT_EQ(puzzleExtracted[0].result.getRawValue(), 42);
    ASSERT_EQ(puzzleExtracted[0].values.size(), 2);
    EXPECT_EQ(puzzleExtracted[0].values[0], 6);
    EXPECT_EQ(puzzleExtracted[0].values[1], 7);
}