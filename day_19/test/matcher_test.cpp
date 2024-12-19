#include "../lib/matcher.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace aoc::day_19;

class MatcherTest : public ::testing::Test {
  protected:
    pattern_matcher createMatcher(std::vector<std::string> patterns) {
        return pattern_matcher{std::move(patterns)};
    }
};

TEST_F(MatcherTest, EmptyPatternListCannotConstructAnything) {
    // Arrange
    auto matcher = createMatcher({});

    // Act
    bool result = matcher.can_construct("test");

    // Assert
    EXPECT_FALSE(result);
}

TEST_F(MatcherTest, EmptyStringCanBeConstructed) {
    // Arrange
    auto matcher = createMatcher({"a"});

    // Act
    bool result = matcher.can_construct("");

    // Assert
    EXPECT_TRUE(result);
}

TEST_F(MatcherTest, SinglePatternMatchesExactly) {
    // Arrange
    auto matcher = createMatcher({"abc"});

    // Act
    bool result = matcher.can_construct("abc");

    // Assert
    EXPECT_TRUE(result);
}

class PatternMatchingParameterizedTest
    : public ::testing::TestWithParam<std::tuple<std::vector<std::string>, std::string, bool>> {};

TEST_P(PatternMatchingParameterizedTest, MatchesCorrectly) {
    // Arrange
    auto const [patterns, design, expected] = GetParam();
    auto matcher = pattern_matcher{patterns};

    // Act
    bool result = matcher.can_construct(design);

    // Assert
    EXPECT_EQ(result, expected);
}

INSTANTIATE_TEST_SUITE_P(MatcherVariations, PatternMatchingParameterizedTest,
                         ::testing::Values(std::make_tuple(std::vector<std::string>{"a", "b"}, "ab", true),
                                           std::make_tuple(std::vector<std::string>{"a", "b"}, "ba", true),
                                           std::make_tuple(std::vector<std::string>{"a", "b"}, "ca", false),
                                           std::make_tuple(std::vector<std::string>{"aa", "a"}, "aaa", true),
                                           std::make_tuple(std::vector<std::string>{"abc", "def"}, "abcdef", true),
                                           std::make_tuple(std::vector<std::string>{"abc", "def"}, "defabc", true),
                                           std::make_tuple(std::vector<std::string>{"abc", "def"}, "deabcf", false)));

class CountingTest : public ::testing::Test {};

TEST_F(CountingTest, EmptyStringHasOneWayToConstruct) {
    // Arrange
    auto matcher = pattern_matcher{{"a"}};

    // Act
    auto count = matcher.count_unique_ways_to_construct("");

    // Assert
    EXPECT_EQ(count, 1);
}

TEST_F(CountingTest, SinglePatternHasOneWayToConstruct) {
    // Arrange
    auto matcher = pattern_matcher{{"abc"}};

    // Act
    auto count = matcher.count_unique_ways_to_construct("abc");

    // Assert
    EXPECT_EQ(count, 1);
}

class CountingParameterizedTest
    : public ::testing::TestWithParam<std::tuple<std::vector<std::string>, std::string, size_t>> {};

TEST_P(CountingParameterizedTest, CountsWaysCorrectly) {
    // Arrange
    auto const [patterns, design, expected_count] = GetParam();
    auto matcher = pattern_matcher{patterns};

    // Act
    auto count = matcher.count_unique_ways_to_construct(design);

    // Assert
    EXPECT_EQ(count, expected_count);
}

INSTANTIATE_TEST_SUITE_P(CountingVariations, CountingParameterizedTest,
                         ::testing::Values(std::make_tuple(std::vector<std::string>{"a"}, "a", 1),
                                           std::make_tuple(std::vector<std::string>{"a", "aa"}, "aa", 2),
                                           std::make_tuple(std::vector<std::string>{"a", "b"}, "ab", 1),
                                           std::make_tuple(std::vector<std::string>{"abc", "ab", "c"}, "abc", 2)));
