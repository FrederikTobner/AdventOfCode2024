#include "../lib/multiset_column_lexer.hpp"
#include <gtest/gtest.h>

class MultiSetColumnLexerTest : public ::testing::Test {
  protected:
    void assertSetsEqual(std::multiset<int64_t> const & expected, std::multiset<int64_t> const & actual) {
        ASSERT_EQ(expected.size(), actual.size());
        for (auto const & value : expected) {
            EXPECT_EQ(actual.count(value), expected.count(value));
        }
    }
};

TEST_F(MultiSetColumnLexerTest, ValidInput_Sequential) {
    auto result = aoc::lexer::tokenize("1 2\n4 5\n7 8", aoc::lexer::ProcessingMode::Sequential);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(MultiSetColumnLexerTest, ValidInput_Parallel) {
    auto result = aoc::lexer::tokenize("1 2\n4 5\n7 8", aoc::lexer::ProcessingMode::Parallel);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(MultiSetColumnLexerTest, EmptyInput) {
    auto result = aoc::lexer::tokenize("");
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.empty());
}

TEST_F(MultiSetColumnLexerTest, WhitespaceOnly) {
    auto result = aoc::lexer::tokenize("  \n\t\r  \n  ");
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.empty());
}

TEST_F(MultiSetColumnLexerTest, SingleLine) {
    auto result = aoc::lexer::tokenize("42 99");
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({42}, first);
    assertSetsEqual({99}, second);
}

TEST_F(MultiSetColumnLexerTest, InvalidNumber) {
    auto result = aoc::lexer::tokenize("1 2\nabc def\n3 4");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(MultiSetColumnLexerTest, MissingNumber) {
    auto result = aoc::lexer::tokenize("1 2\n3\n4 5");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(MultiSetColumnLexerTest, ExtraNumbers) {
    auto result = aoc::lexer::tokenize("1 2\n3 4 5\n6 7");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(MultiSetColumnLexerTest, MultipleWhitespace) {
    auto result = aoc::lexer::tokenize("1   2\n  4  5   \n7    8");
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(MultiSetColumnLexerTest, TabSeparated) {
    auto result = aoc::lexer::tokenize("1\t2\n4\t5\n7\t8");
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}