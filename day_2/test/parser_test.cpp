#include "../lib/parser.hpp"
#include <gtest/gtest.h>

class ParserTest : public testing::Test {
  protected:
    const std::vector<std::vector<uint8_t>> empty{};
};

TEST_F(ParserTest, HandlesEmptyInput) {
    EXPECT_EQ(parser::parseInput("")->size(), 0);
    EXPECT_EQ(parser::parseInput("\n")->size(), 0);
    EXPECT_EQ(parser::parseInput("  \t\n  ")->size(), 0);
}

TEST_F(ParserTest, ParsesSingleLine) {
    auto result = parser::parseInput("1 2 3");
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 1);
    auto expected = std::vector<uint8_t>{1, 2, 3};
    EXPECT_EQ((*result)[0], expected);
}

TEST_F(ParserTest, ParsesMultipleLines) {
    auto result = parser::parseInput("1 2 3\n4 5 6\n7 8 9");
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 3);
    EXPECT_EQ(*result, (std::vector<std::vector<uint8_t>>{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
}

TEST_F(ParserTest, HandlesWhitespace) {
    auto result = parser::parseInput("  1  2  3  \n\n  4  5  6  \n  ");
    ASSERT_TRUE(result);
    EXPECT_EQ(*result, (std::vector<std::vector<uint8_t>>{{1, 2, 3}, {4, 5, 6}}));
}

TEST_F(ParserTest, DetectsInvalidInput) {
    EXPECT_FALSE(parser::parseInput("1 2 a"));
    EXPECT_FALSE(parser::parseInput("1 2 3\n4 b 6"));
    EXPECT_FALSE(parser::parseInput("256 1 2"));
}