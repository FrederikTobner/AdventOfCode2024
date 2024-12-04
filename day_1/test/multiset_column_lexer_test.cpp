#include "../../shared/src/column_lexer.hpp"
#include "../lib/lexer_rule.hpp"
#include <gtest/gtest.h>

class ColumnLexerTest : public ::testing::Test {
  protected:
    void assertSetsEqual(std::multiset<int64_t> const & expected, std::multiset<int64_t> const & actual) {
        ASSERT_EQ(expected.size(), actual.size());
        for (auto const & value : expected) {
            EXPECT_EQ(actual.count(value), expected.count(value));
        }
    }
};

TEST_F(ColumnLexerTest, ValidInput_Sequential) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2>("1 2\n4 5\n7 8", aoc::lexer::rules::numberProducer,
                                                                std::execution::seq);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ColumnLexerTest, ValidInput_Parallel) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2>("1 2\n4 5\n7 8", aoc::lexer::rules::numberProducer,
                                                                std::execution::par_unseq);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ColumnLexerTest, EmptyInput) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2>("", aoc::lexer::rules::numberProducer);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.empty());
}

TEST_F(ColumnLexerTest, WhitespaceOnly) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2>("  \n\t\r  \n  ", aoc::lexer::rules::numberProducer);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.empty());
}

TEST_F(ColumnLexerTest, SingleLine) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2>("42 99", aoc::lexer::rules::numberProducer);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({42}, first);
    assertSetsEqual({99}, second);
}

TEST_F(ColumnLexerTest, InvalidNumber) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2>("1 2\nabc def\n3 4", aoc::lexer::rules::numberProducer);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(ColumnLexerTest, MissingNumber) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2>("1 2\n3\n4 5", aoc::lexer::rules::numberProducer);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(ColumnLexerTest, ExtraNumbers) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2>("1 2\n3 4 5\n6 7", aoc::lexer::rules::numberProducer);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(ColumnLexerTest, MultipleWhitespace) {
    auto result =
        aoc::lexer::columnbased::tokenize<int64_t, 2>("1   2\n  4  5   \n7    8", aoc::lexer::rules::numberProducer);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ColumnLexerTest, TabSeparated) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2>("1\t2\n4\t5\n7\t8", aoc::lexer::rules::numberProducer);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}
