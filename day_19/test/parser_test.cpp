#include "../lib/parser.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc::day_19;

class ParserTest : public ::testing::Test {
  protected:
    void SetUp() override {
    }
};

TEST_F(ParserTest, EmptyInputReturnsError) {
    // Arrange
    std::string_view input = "";

    // Act
    auto result = parseInput(input);

    // Assert
    EXPECT_FALSE(result.has_value());
}

TEST_F(ParserTest, ValidInputIsParsedCorrectly) {
    // Arrange
    std::string_view input = "ab,cd\n\nefgh\nijkl";

    // Act
    auto result = parseInput(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    EXPECT_THAT(result->patterns, ::testing::ElementsAre("ab", "cd"));
    EXPECT_THAT(result->designs, ::testing::ElementsAre("efgh", "ijkl"));
}

TEST_F(ParserTest, HandlesWindowsLineEndings) {
    // Arrange
    std::string_view input = "ab,cd\r\n\r\nefgh\r\nijkl";

    // Act
    auto result = parseInput(input);

    // Assert
    ASSERT_TRUE(result.has_value());
    EXPECT_THAT(result->patterns, ::testing::ElementsAre("ab", "cd"));
    EXPECT_THAT(result->designs, ::testing::ElementsAre("efgh", "ijkl"));
}

class ParserParameterizedTest : public ::testing::TestWithParam<std::tuple<std::string, std::vector<std::string>>> {};

TEST_P(ParserParameterizedTest, PatternsAreParsedCorrectly) {
    // Arrange
    auto const [input, expected_patterns] = GetParam();
    auto const full_input = input + "\n\ndesign";

    // Act
    auto result = parseInput(full_input);

    // Assert
    ASSERT_TRUE(result.has_value());
    EXPECT_THAT(result->patterns, ::testing::ElementsAreArray(expected_patterns));
}

INSTANTIATE_TEST_SUITE_P(PatternVariations, ParserParameterizedTest,
                         ::testing::Values(std::make_tuple("a,b", std::vector<std::string>{"a", "b"}),
                                           std::make_tuple("abc, def", std::vector<std::string>{"abc", "def"}),
                                           std::make_tuple("a,b,c", std::vector<std::string>{"a", "b", "c"})));
