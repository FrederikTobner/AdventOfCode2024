#include "../src/column_lexer.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <expected>
#include <set>
#include <string_view>
#include <system_error>

class ColumnLexerTest : public ::testing::Test {
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

auto handle_int64_t(std::string_view token) -> std::expected<uint64_t, std::error_code> {
    uint8_t value;
    auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), value);
    if (ec != std::errc()) {
        return std::unexpected(std::make_error_code(ec));
    }
    return value;
}

TEST_F(ColumnLexerTest, UsingSetAsTokenContainer) {
    auto result =
        aoc::lexer::columnbased::tokenize<int64_t, 2, std::set>("1 2\n1 5\n7 8", handle_int64_t, std::execution::seq);
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}

TEST_F(ColumnLexerTest, UsingAnotherDelimiter) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2, std::vector>("1,2\n1,5\n7,8", handle_int64_t,
                                                                             std::execution::seq, ',');
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    auto expectedFirst = std::vector<int64_t>{1, 1, 7};
    auto expectedSecond = std::vector<int64_t>{2, 5, 8};
    ASSERT_TRUE(std::ranges::equal(first, expectedFirst));
    ASSERT_TRUE(std::ranges::equal(second, expectedSecond));
}

TEST_F(ColumnLexerTest, TrimsWhiteSpaceCharactersAroundTokens) {
    auto result = aoc::lexer::columnbased::tokenize<int64_t, 2, std::set>(" 1 , 2 \n 1 , \t\t5  \n 7 ,  8 ",
                                                                          handle_int64_t, std::execution::seq, ',');
    ASSERT_TRUE(result) << result.error().message();

    auto const & [first, second] = *result;
    assertSetsEqual({1, 7}, first);
    assertSetsEqual({2, 5, 8}, second);
}