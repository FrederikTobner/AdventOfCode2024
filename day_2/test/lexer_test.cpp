#include "../../shared/lexer.hpp"
#include "../lib/lexer_rule.hpp"
#include <gtest/gtest.h>

class LexerTest : public testing::Test {
  protected:
    const std::vector<std::vector<uint8_t>> empty{};
};

TEST_F(LexerTest, HandlesEmptyInput) {
    EXPECT_EQ(aoc::lexer::tokenize<uint8_t>("", aoc::lexer::rules::handleToken)->size(), 0);
    EXPECT_EQ(aoc::lexer::tokenize<uint8_t>("\n", aoc::lexer::rules::handleToken)->size(), 0);
    EXPECT_EQ(aoc::lexer::tokenize<uint8_t>("  \t\n  ", aoc::lexer::rules::handleToken)->size(), 0);
}

TEST_F(LexerTest, ParsesSingleLine) {
    auto result = aoc::lexer::tokenize<uint8_t>("1 2 3", aoc::lexer::rules::handleToken);
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 1);
    auto expected = std::vector<uint8_t>{1, 2, 3};
    EXPECT_EQ((*result)[0], expected);
}

TEST_F(LexerTest, ParsesMultipleLines) {
    auto result = aoc::lexer::tokenize<uint8_t>("1 2 3\n4 5 6\n7 8 9", aoc::lexer::rules::handleToken);
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 3);
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{4, 5, 6}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{7, 8, 9}) != result->end());
}

TEST_F(LexerTest, HandlesWhitespace) {
    auto result = aoc::lexer::tokenize<uint8_t>("  1  2  3  \n\n  4  5  6  \n  ", aoc::lexer::rules::handleToken);
    ASSERT_TRUE(result);
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{4, 5, 6}) != result->end());
}

TEST_F(LexerTest, DetectsInvalidInput) {
    EXPECT_FALSE(aoc::lexer::tokenize<uint8_t>("1 2 a", aoc::lexer::rules::handleToken));
    EXPECT_FALSE(aoc::lexer::tokenize<uint8_t>("1 2 3\n4 b 6", aoc::lexer::rules::handleToken));
    EXPECT_FALSE(aoc::lexer::tokenize<uint8_t>("256 1 2", aoc::lexer::rules::handleToken));
}

TEST_F(LexerTest, TabSeparated) {
    auto result = aoc::lexer::tokenize<uint8_t>("1\t2\t3\n4\t5\t6\n7\t8\t9", aoc::lexer::rules::handleToken);
    ASSERT_TRUE(result);
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{4, 5, 6}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{7, 8, 9}) != result->end());
}
