#include "../src/column_splitter.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <expected>
#include <set>
#include <string_view>
#include <system_error>

class ColumnSplitterTest : public ::testing::Test {
  protected:
    void assertSetsEqual(std::multiset<int64_t> const & expected, std::multiset<int64_t> const & actual) {
        ASSERT_EQ(expected.size(), actual.size());
        for (auto const & value : expected) {
            EXPECT_EQ(actual.count(value), expected.count(value));
        }
    }
    void assertSetsEqual(std::set<int64_t> const & expected, std::set<int64_t> const & actual) {
        ASSERT_EQ(expected.size(), actual.size());
        for (auto const & value : expected) {
            EXPECT_EQ(actual.count(value), expected.count(value));
        }
    }
};

auto handle_int64_t = [](std::string_view token) -> std::expected<int64_t, std::error_code> {
    int64_t value;
    auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), value);
    if (ec != std::errc()) {
        return std::unexpected(std::make_error_code(ec));
    }
    return value;
};

TEST_F(ColumnSplitterTest, ValidInput_Sequential) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("1 2\n4 5\n7 8", handle_int64_t,
                                                                               std::execution::seq);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ColumnSplitterTest, ValidInput_Parallel) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("1 2\n4 5\n7 8", handle_int64_t,
                                                                               std::execution::par_unseq);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ColumnSplitterTest, EmptyInput) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("", handle_int64_t);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.empty());
}

TEST_F(ColumnSplitterTest, WhitespaceOnly) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("  \n\t\r  \n  ", handle_int64_t);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    EXPECT_TRUE(first.empty());
    EXPECT_TRUE(second.empty());
}

TEST_F(ColumnSplitterTest, SingleLine) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("42 99", handle_int64_t);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({42}, first);
    assertSetsEqual({99}, second);
}

TEST_F(ColumnSplitterTest, InvalidNumber) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("1 2\nabc def\n3 4", handle_int64_t);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(ColumnSplitterTest, MissingNumber) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("1 2\n3\n4 5", handle_int64_t);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(ColumnSplitterTest, ExtraNumbers) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("1 2\n3 4 5\n6 7", handle_int64_t);
    ASSERT_FALSE(result);
    EXPECT_EQ(result.error(), std::make_error_code(std::errc::invalid_argument));
}

TEST_F(ColumnSplitterTest, MultipleWhitespace) {
    auto result =
        aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("1   2\n  4  5   \n7    8", handle_int64_t);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ColumnSplitterTest, TabSeparated) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::multiset>("1\t2\n4\t5\n7\t8", handle_int64_t);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 4, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ColumnSplitterTest, UsingSetAsTokenContainer) {
    auto result =
        aoc::splitter::columnbased::split<int64_t, 2, std::set>("1 2\n1 5\n7 8", handle_int64_t, std::execution::seq);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ColumnSplitterTest, UsingAnotherDelimiter) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::vector>("1,2\n1,5\n7,8", handle_int64_t,
                                                                             std::execution::seq, ',');
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    auto expectedFirst = std::vector<int64_t>{1, 1, 7};
    auto expectedSecond = std::vector<int64_t>{2, 5, 8};
    ASSERT_TRUE(std::ranges::equal(first, expectedFirst));
    ASSERT_TRUE(std::ranges::equal(second, expectedSecond));
}

TEST_F(ColumnSplitterTest, TrimsWhiteSpaceCharactersAroundTokens) {
    auto result = aoc::splitter::columnbased::split<int64_t, 2, std::set>(" 1 , 2 \n 1 , \t\t5  \n 7 ,  8 ",
                                                                          handle_int64_t, std::execution::seq, ',');
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}