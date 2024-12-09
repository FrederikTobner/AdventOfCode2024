#include "../src/line_splitter.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <charconv>
#include <cstdint>
#include <expected>
#include <ranges>
#include <set>
#include <string_view>
#include <system_error>

#include "../src/ranges_compatibility_layer.hpp"

class LineSplitterTest : public testing::Test {
  protected:
    const std::vector<std::vector<uint8_t>> empty{};
};

auto handle_uint8_t = [](std::string_view token) -> std::expected<uint8_t, std::error_code> {
    uint8_t value;
    auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), value);
    if (ec != std::errc()) {
        return std::unexpected(std::make_error_code(ec));
    }
    return value;
};

TEST_F(LineSplitterTest, HandlesEmptyInput) {
    EXPECT_EQ(aoc::splitter::linebased::split<uint8_t>("", handle_uint8_t)->size(), 0);
    EXPECT_EQ(aoc::splitter::linebased::split<uint8_t>("\n", handle_uint8_t)->size(), 0);
    EXPECT_EQ(aoc::splitter::linebased::split<uint8_t>("  \t\n  ", handle_uint8_t)->size(), 0);
}

TEST_F(LineSplitterTest, ParsesSingleLine) {
    // Arrange
    auto input = "1 2 3";
    auto expected = std::vector<uint8_t>{1, 2, 3};

    // Act
    auto result = aoc::splitter::linebased::split<uint8_t>(input, handle_uint8_t);

    // Assert
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 1);
    EXPECT_EQ((*result)[0], expected);
}

TEST_F(LineSplitterTest, ParsesMultipleLines) {
    // Arrange
    auto input = "1 2 3\n4 5 6\n7 8 9";

    // Act
    auto result = aoc::splitter::linebased::split<uint8_t>(input, handle_uint8_t);

    // Assert
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 3);
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{4, 5, 6}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{7, 8, 9}) != result->end());
}

TEST_F(LineSplitterTest, HandlesWhitespace) {
    // Arrange
    auto input = "  1  2  3  \n\n  4  5  6  \n  ";

    // Act
    auto result = aoc::splitter::linebased::split<uint8_t>(input, handle_uint8_t);

    // Assert
    ASSERT_TRUE(result);
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{4, 5, 6}) != result->end());
}

TEST_F(LineSplitterTest, DetectsInvalidInput) {
    EXPECT_FALSE(aoc::splitter::linebased::split<uint8_t>("1 2 a", handle_uint8_t));
    EXPECT_FALSE(aoc::splitter::linebased::split<uint8_t>("1 2 3\n4 b 6", handle_uint8_t));
    EXPECT_FALSE(aoc::splitter::linebased::split<uint8_t>("256 1 2", handle_uint8_t));
}

TEST_F(LineSplitterTest, TabSeparated) {
    // Arrange
    auto input = "1\t2\t3\n4\t5\t6\n7\t8\t9";

    // Act
    auto result = aoc::splitter::linebased::split<uint8_t>(input, handle_uint8_t);

    // Assert
    ASSERT_TRUE(result);
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{4, 5, 6}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::vector<uint8_t>{7, 8, 9}) != result->end());
}

TEST_F(LineSplitterTest, UsingSetAsTokenContainer) {
    // Arrange
    auto input = "1 2 3\n2 2 1\n1 1 1";

    // Act
    auto result = aoc::splitter::linebased::split<uint8_t, std::set>(input, handle_uint8_t);

    // Assert
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 3);
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{2, 1}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1}) != result->end());
}

TEST_F(LineSplitterTest, UsingAnotherDelimiter) {
    // Arrange
    auto input = "1,2,3\n2,2,1\n1,1,1";

    // Act
    auto result = aoc::splitter::linebased::split<uint8_t, std::set>(input, handle_uint8_t, ',');

    // Assert
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 3);
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{2, 1}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1}) != result->end());
}

TEST_F(LineSplitterTest, TrimsWhiteSpaceCharactersAroundTokens) {
    // Arrange
    auto input = " 1 ,  2 \t\t ,\t 3 \n 2  , 2,1 \n 1 ,\t1,\t1\t";

    // Act
    auto result = aoc::splitter::linebased::split<uint8_t, std::set>(input, handle_uint8_t, ',');

    // Assert
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 3);
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{2, 1}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1}) != result->end());
}
