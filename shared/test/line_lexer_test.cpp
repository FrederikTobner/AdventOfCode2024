#include "../src/line_lexer.hpp"

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

class LexerTest : public testing::Test {
  protected:
    const std::vector<std::vector<uint8_t>> empty{};
};

auto handleToken(std::string_view token) -> std::expected<uint8_t, std::error_code> {
    uint8_t value;
    auto [ptr, ec] = std::from_chars(token.data(), token.data() + token.size(), value);
    if (ec != std::errc()) {
        return std::unexpected(std::make_error_code(ec));
    }
    return value;
}

TEST_F(LexerTest, UsingSetAsTokenContainer) {
    auto result = aoc::lexer::linebased::tokenize<uint8_t, std::set>("1 2 3\n2 2 1\n1 1 1", handleToken);
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 3);
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{2, 1}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1}) != result->end());
}

TEST_F(LexerTest, UsingCommaAsDelimiter) {
    auto result = aoc::lexer::linebased::tokenize<uint8_t, std::set>("1, 2,3\n2,2,1\n1,1,1", handleToken, ',');
    ASSERT_TRUE(result);
    EXPECT_EQ(result->size(), 3);
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1, 2, 3}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{2, 1}) != result->end());
    EXPECT_TRUE(std::ranges::find(*result, std::set<uint8_t>{1}) != result->end());
}
