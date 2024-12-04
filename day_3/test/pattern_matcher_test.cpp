#include "../lib/pattern_matcher.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(PatternMatcher, FindsMatches) {
    std::string text = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

    auto matches = aoc::pattern_matcher::findMultiplicationPairs(text);
    ASSERT_EQ(matches.size(), 4);
    ASSERT_EQ(matches[0].first, 2);
    ASSERT_EQ(matches[0].second, 4);
    ASSERT_EQ(matches[1].first, 5);
    ASSERT_EQ(matches[1].second, 5);
    ASSERT_EQ(matches[2].first, 11);
    ASSERT_EQ(matches[2].second, 8);
    ASSERT_EQ(matches[3].first, 8);
    ASSERT_EQ(matches[3].second, 5);
}

TEST(PatternMatcher, FindsMatches2) {
    std::string text = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";

    auto matches = aoc::pattern_matcher::findMultiplicationPairsWithToggle(text);
    ASSERT_EQ(matches.size(), 2);
    ASSERT_EQ(matches[0].first, 2);
    ASSERT_EQ(matches[0].second, 4);
    ASSERT_EQ(matches[1].first, 8);
    ASSERT_EQ(matches[1].second, 5);
}