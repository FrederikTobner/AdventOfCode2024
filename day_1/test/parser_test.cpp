#include "../lib/parser.hpp"
#include <gtest/gtest.h>

class ParserTest : public ::testing::Test {
  protected:
    void assertSetsEqual(std::multiset<int64_t> const & expected, std::multiset<int64_t> const & actual) {
        ASSERT_EQ(expected.size(), actual.size());
        for (auto const & value : expected) {
            EXPECT_EQ(actual.count(value), expected.count(value));
        }
    }
};

TEST_F(ParserTest, ValidInput_Sequential) {
    auto result = parser::parseInput("1 2\n4 5\n7 8", parser::ProcessingMode::Sequential);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ParserTest, ValidInput_Parallel) {
    auto result = parser::parseInput("1 2\n4 5\n7 8", parser::ProcessingMode::Parallel);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ParserTest, EmptyInput) {
    auto result = parser::parseInput("");
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.empty());
}

TEST_F(ParserTest, WhitespaceOnly) {
    auto result = parser::parseInput("  \n\t\r  \n  ");
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.empty());
}

TEST_F(ParserTest, SingleLine) {
    auto result = parser::parseInput("42 99");
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({42}, first);
    assertSetsEqual({99}, second);
}

TEST_F(ParserTest, InvalidNumber) {
    auto result = parser::parseInput("1 2\nabc def\n3 4");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(ParserTest, MissingNumber) {
    auto result = parser::parseInput("1 2\n3\n4 5");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(ParserTest, ExtraNumbers) {
    auto result = parser::parseInput("1 2\n3 4 5\n6 7");
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(ParserTest, MultipleWhitespace) {
    auto result = parser::parseInput("1   2\n  4  5   \n7    8");
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}
