#include "../lib/page_ordering_rule.hpp"
#include "../lib/page_update.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>


using testing::ElementsAre;

class PageUpdateTest : public ::testing::Test {
  protected:
    // Simple rule where 1 must come before 2
    aoc::day_5::page_ordering_rule basic_rule{1, 2};
};

TEST_F(PageUpdateTest, FindRulePagesReturnsNulloptWhenPrePageNotPresent) {
    aoc::day_5::page_update update({2, 3, 4});
    EXPECT_FALSE(update.find_rule_pages(basic_rule).has_value());
}

TEST_F(PageUpdateTest, FindRulePagesReturnsNulloptWhenPostPageNotPresent) {
    aoc::day_5::page_update update({1, 3, 4});
    EXPECT_FALSE(update.find_rule_pages(basic_rule).has_value());
}

TEST_F(PageUpdateTest, FindRulePagesReturnsMatchWhenBothPagesPresent) {
    aoc::day_5::page_update update({1, 3, 2});
    auto match = update.find_rule_pages(basic_rule);
    EXPECT_TRUE(match.has_value());
    EXPECT_FALSE(match->needs_swap());
}

TEST_F(PageUpdateTest, FindRulePagesIndicatesSwapNeededWhenOrderIncorrect) {
    aoc::day_5::page_update update({2, 3, 1});
    auto match = update.find_rule_pages(basic_rule);
    EXPECT_TRUE(match.has_value());
    EXPECT_TRUE(match->needs_swap());
}

TEST_F(PageUpdateTest, FixSwapsElementsWhenNeeded) {
    aoc::day_5::page_update update({2, 3, 1});
    auto match = update.find_rule_pages(basic_rule);
    ASSERT_TRUE(match.has_value());
    aoc::day_5::page_update::fix(*match);
    // Verify the fix worked by checking if a new match needs swapping
    auto new_match = update.find_rule_pages(basic_rule);
    EXPECT_TRUE(new_match.has_value());
    EXPECT_FALSE(new_match->needs_swap());
}

TEST_F(PageUpdateTest, HandlesElementsAtEdges) {
    aoc::day_5::page_update update({2, 3, 4, 5, 1}); // 1 at end, 2 at start
    auto match = update.find_rule_pages(basic_rule);
    ASSERT_TRUE(match.has_value());
    EXPECT_TRUE(match->needs_swap());
    aoc::day_5::page_update::fix(*match);
    auto new_match = update.find_rule_pages(basic_rule);
    EXPECT_TRUE(new_match.has_value());
    EXPECT_FALSE(new_match->needs_swap());
}

TEST_F(PageUpdateTest, GetMiddleElementReturnsCorrectValue) {
    aoc::day_5::page_update update({1, 2, 3});
    EXPECT_EQ(update.getMiddleElement(), 2);
}
